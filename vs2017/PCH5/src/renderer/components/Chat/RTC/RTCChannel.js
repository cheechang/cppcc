/**
 * Wraps a DataChannel between two Peers.
 */

const logger = require('./logger')('Peer')
// const Message = require('./Message')

const CHUNK_MTU = 16000
const CHUNKS_PER_ACK = 64

class RTCChannel {
    constructor(peer) {
        logger.debug('constructor()')

        // let id = Negotiator._idPrefix + util.randomToken()
        // optional: [{
        //     RtpDataChannels: true,
        //     reliable: options.reliable
        // }]
        this.outgoingFiles = {}
        this.incomingFiles = {}

        this.peer = peer

        this._dc = peer.pc.createDataChannel(label, config)
        this._dc.binaryType = 'arraybuffer'


        initListener()
    }
    initListener() {
        self = this
        // pc.onnegotiationneeded() {
        this.pc.ondatachannel = onDataChannel
        // }
    
        this._dc.onopen = (event) => {
            util.log('Data channel connection success')
        }
        this._dc.onclose = (event) => {
            util.log('DataChannel closed for:', self.peer)
            self.close()
        }

        this._dc.onmessage = (event) => {
            if (data.byteLength !== undefined) {
                self._onBinaryData(e.data)
            } else {
                self._onJSONData(e.data)
            }
        }
        this._dc.ondatachannel = (event) => {
            util.log('DataChannel closed for:', self.peer)
        }

        this._dc.onerror = (event) => {
            util.log('DataChannel closed for:', self.peer)
            self.close()
        }

        this._dc.onbufferedamountlow = (event) => {
            util.log('DataChannel closed for:', self.peer)
        }
    }

    _onBinaryData(data) {
        var self = this,
            incoming = this.files.incoming[connection.peer],
            info = incoming.info,
            file = incoming.file,
            block = incoming.block,
            receivedChunkNum = incoming.receivedChunkNum,
            chunksPerAck = WebRTC.CHUNKS_PER_ACK,
            nextChunkNum, lastChunkInFile, lastChunkInBlock

        // TODO move it after requesting a new block to speed things up
        emit('receiving_progress', (receivedChunkNum + 1) / info.chunksTotal)
        // console.log('Got chunk no ' + (receivedChunkNum + 1) + ' out of ' + info.chunksTotal)

        block.push(data)

        nextChunkNum = incoming.receivedChunkNum = receivedChunkNum + 1
        lastChunkInFile = receivedChunkNum === info.chunksTotal - 1
        lastChunkInBlock = receivedChunkNum > 0 && ((receivedChunkNum + 1) % chunksPerAck) === 0

        if (lastChunkInFile || lastChunkInBlock) {
            file.append(block).then(function () {
                if (lastChunkInFile) {
                    file.save()
                } else {
                    // console.log('Requesting block starting at: ' + (nextChunkNum))
                    incoming.block = []
                    self._requestFileBlock(nextChunkNum)
                }
            })
        }
    }

    _onJSONData(data, connection) {
        switch (data.type) {
            case 'info':
                var info = data.payload

                // Store incoming file info for later
                this.files.incoming = {
                    info: info,
                    file: null,
                    block: [],
                    receivedChunkNum: 0
                }

                console.log('Peer:\t File info: ', data)
                break

            case 'cancel':
                console.log('Peer:\t Sender canceled file transfer')
                break

            case 'response':
                var response = data.payload

                // If recipient rejected the file, delete stored file
                if (!response) {
                    delete this.files.outgoing
                }

                console.log('Peer:\t File response: ', data)
                break

            case 'block_request':
                var file = this.files.outgoing.file

                // console.log('Peer:\t Block request: ', data.payload)

                this._sendBlock(connection, file, data.payload)
                break
            default:
                console.log('Peer:\t Unknown message: ', data)
        }
    }

    getFileInfo(file) {
        return {
            lastModifiedDate: file.lastModifiedDate,
            name: file.name,
            size: file.size,
            type: file.type,
            chunksTotal: Math.ceil(file.size / WebRTC.CHUNK_MTU)
        }
    }

    sendFileInfo(info) {
        var message = {
            type: 'info',
            payload: info
        }

        this._dc.send(JSON.stringify(message))
    }

    sendCancelRequest(connection) {
        var message = {
            type: 'cancel'
        }

        this._dc.send(JSON.stringify(message))
    }

    sendFileResponse(connection, response) {
        var message = {
            type: 'response',
            payload: response
        }

        if (response) {
            // If recipient accepted the file, request required space to store the file on HTML5 filesystem
            var incoming = this.files.incoming[connection.peer],
                info = incoming.info

            new File({ name: info.name, size: info.size, type: info.type })
                .then(function (file) {
                    incoming.file = file
                    this._dc.send(JSON.stringify(message))
                })
        } else {
            // Otherwise, delete stored file info
            delete this.files.incoming[connection.peer]
            this._dc.send(JSON.stringify(message))
        }
    }

    sendFile(connection, file) {
        // Save the file for later
        this.files.outgoing[connection.peer] = {
            file: file,
            info: this.getFileInfo(file)
        }

        // Send the first block. Next ones will be requested by recipient.
        this._sendBlock(connection, file, 0)
    }

    _requestFileBlock(chunkNum) {
        var message = {
            type: 'block_request',
            payload: chunkNum
        }
        send(JSON.stringify(message))
    }

    _sendBlock(connection, file, beginChunkNum) {
        var info = this.files.outgoing[connection.peer].info,
            chunkSize = WebRTC.CHUNK_MTU,
            chunksPerAck = WebRTC.CHUNKS_PER_ACK,
            remainingChunks = info.chunksTotal - beginChunkNum,
            chunksToSend = Math.min(remainingChunks, chunksPerAck),
            endChunkNum = beginChunkNum + chunksToSend - 1,
            begin = beginChunkNum * chunkSize,
            end = endChunkNum * chunkSize + chunkSize,
            reader = new FileReader(),
            blockBlob, chunkNum

        // Read the whole block from file
        blockBlob = file.slice(begin, end)

        // console.log('Sending block: start chunk: ' + beginChunkNum + ' end chunk: ' + endChunkNum)
        // console.log('Sending block: start byte : ' + begin + ' end byte : ' + end)

        reader.onload = (event) => {
            if (reader.readyState === FileReader.DONE) {
                var blockBuffer = event.target.result

                for (chunkNum = beginChunkNum; chunkNum < endChunkNum + 1; chunkNum++) {
                    // Send each chunk (begin index is inclusive, end index is exclusive)
                    var begin = (chunkNum % chunksPerAck) * chunkSize,
                        end = Math.min(begin + chunkSize, blockBuffer.byteLength),
                        chunkBuffer = blockBuffer.slice(begin, end)

                    this._dc.send(chunkBuffer)

                    // console.log('Sent chunk: start byte: ' + begin + ' end byte: ' + end + ' length: ' + chunkBuffer.byteLength)
                    // console.log('Sent chunk no ' + (chunkNum + 1) + ' out of ' + info.chunksTotal)

                    connection.emit('sending_progress', (chunkNum + 1) / info.chunksTotal)
                }
            }
        }

        reader.readAsArrayBuffer(blockBlob)
    }
}