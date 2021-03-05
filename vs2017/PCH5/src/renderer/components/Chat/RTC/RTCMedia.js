
/**
 * Wraps the streaming interface between two Peers.
 */
const EventEmitter = require('events').EventEmitter
const logger = require('./logger')('Peer')
// const session = require('./RTCSession')


class RTCMedia extends EventEmitter {
  constructor(pc, config) {
    // Interop req for chrome.
    this.optional = { optional: [{ DtlsSrtpKeyAgreement: true }] }

    this.pc = pc
    this.stream = null
    this.audioTrack = null
    this.videoTrack = null
  }

  muteMicphone(isMute) {
    this.audioTrack.enabled = !isMute
  }

  disableCamera(isDisable) {
    this.videoTrack.enabled = !isDisable
  }
}

class MediaLocal extends RTCMedia {
  constructor(pc, config) {
    logger.debug('constructor()')
    super(pc, config)

    this.screenTrack = null

    _getTracks(config.constraints)
    _getScreenTrack()
  }

  _getTracks() {
    navigator.mediaDevices.getUserMedia(constraints)
      .then((stream) => {
        stream.oninactive = function () {
          console.log('Stream inactive');
        };
        this.stream = stream
        this.pc.addStream(stream)
        this.videoTrack = stream.getVideoTracks()[0]
        this.audioTrack = stream.getAudeoTracks()[0]
      })
      .catch((error) => {
        log.error(error.name, error)
      })
  }

  _getScreenTrack() {
    desktopCapturer.getSources({ types: ['screen'] }, (error, sources) => {
      for (src of sources) {
        if (src.id == 'screen:0:0') {
          navigator.webkitGetUserMedia(
            {
              audio: false,
              video: {
                mandatory: {
                  chromeMediaSource: 'desktop',
                  chromeMediaSourceId: src.id,
                  maxWidth: 1280,
                  maxHeight: 720
                }
              }
            },
            function gotStream(stream) {
              this.videoTrack = stream.getVideoTracks()[0]
            },
            function getUserMediaError(e) {
              logger.error('getUserMediaError', e)
            }
          )
        }
      }
    })
  }

  shareScreen(isEnable) {

  }
}

class MediaRemote extends RTCMedia {
  constructor(pc, config) {
    logger.debug('constructor()')
    super(pc, config)

    this.pc.ontrack = this.onGetTracks;
  }

  onGetTracks(event) {
    // this.event.streams[0];
    this.videoTrack = event.streams[0].getVideoTracks()[0]
    this.audioTrack = event.streams[0].getAudeoTracks()[0]
  }
}