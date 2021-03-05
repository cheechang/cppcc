var vrv = vrv || {};
vrv.jssdk = {};
vrv.util = {};
vrv._init = {};
vrv._ready = {};
vrv.callpc = {};
vrv._ready.fn = {};
vrv.pc = {
    getAccountInfo: function (a) {
        vrv.callpc.getAccountInfo(a)
    },
    getContactList: function (a) {
        console.log(a, 'jssdk contant-------');
        vrv.callpc.getContactList(a)
    },
    getServerName: function (a) {
        // vrv.callpc.getServerName(a)
    },
    addComment: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addComment'));
    },
    deleteComment: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'deleteComment'));
    },
    getCommentByPage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getCommentByPage'));
    },
    commentCount: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'commentCount'));
    },
    addPraise: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addPraise'));
    },
    deletePraise: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'deletePraise'));
    },
    getPraiseByPage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getPraiseByPage'));
    },
    getPraisePages: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getPraisePages'));
    },
    praiseCount: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'praiseCount'));
    },
    modifyStatisticCount: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'modifyStatisticCount'));
    },
    getStatisticCount: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getStatisticCount'));
    },
    getCommentRecordByPage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getCommentRecordByPage'));
    },
    getCommentRecordNum: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getCommentRecordNum'));
    },
    addCommentRecord: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addCommentRecord'));
    },
    setCommentRecordRead: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'setCommentRecordRead'));
    },
    setCommentRecordReadBatch: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'setCommentRecordReadBatch'));
    },
    getCommentsByObjectIDs: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getCommentsByObjectIDs'));
    },
    getPraisesByUserIDs: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getPraisesByUserIDs'));
    },
    getShareByPage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getShareByPage'));
    },
    getShareList: function (a) {
        var str = '{"shareParam":{"userID":4328627864,"pageSize":10,"showType":2,"pageNum":1},"commentParam":{"pageSize":10,"pageNum":1,"subjectType":0},"function":"getShareList"}';
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getShareList'));
    },
    getShareByID: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getShareByID'));
    },
    getOwnShareByPage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getOwnShareByPage'));
    },
    deleteShare: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'deleteShare'));
    },
    addShare: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addShare'));
    },
    // 添加权限分享 2018/8/30
    addShareByTemporaryGroup: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addShareByTemporaryGroup'));
    },
    addMessage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addMessage'));
    },
    deleteShareMessage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'deleteShareMessage'));
    },
    addUserGroup: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addUserGroup'));
    },
    updateUserGroup: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'updateUserGroup'));
    },
    deleteUserGroup: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'deleteUserGroup'));
    },
    getUserGroupByID: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getUserGroupByID'));
    },
    getUserGroup: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getUserGroup'));
    },
    getShareUserByPage: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getShareUserByPage'));
    },
    getShareUserNum: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getShareUserNum'));
    },
    addShareUsers: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'addShareUsers'));
    },
    getShareImgList: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getShareImgList'));
    },
    uploadShareImage: function (a) {
        console.log('vrv.jssdk:::uploadShareImage:::', a);
        vrv.callpc.uploadShareImage(a);
    },
    getShareBackgroundIMG: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'getShareBackgroundIMG'));
    },
    uploadShareBackgroundIMG: function (a) {
        vrv.callpc.circleOfFriend(vrv.util.jsonFactory(a, 'uploadShareBackgroundIMG'));
    }
};
vrv.util.jsonFactory = function (params, funtionName) {
    var newArams = params;
    newArams.function = funtionName;
    return newArams;
}
vrv.init = function (options) {
    //添加是否初始化的标识，防止再次初始化
    //alert('init jssdk');
    if (vrv._init.inited) {
        return;
    }
    vrv._init.inited = true;
    var agent = navigator.userAgent.toLowerCase();
	vrv.jssdk = vrv.pc;
    if (agent.indexOf('electron') != -1) {
        var remote = window.require('electron').remote;
        var callByDDIOApp = remote.getGlobal('callByDDIOApp');
        console.log('callByDDIOApp', callByDDIOApp);
        vrv.callpc = callByDDIOApp;
        delete window.module;
        if (typeof vrv._ready.fn == 'function') {
               vrv._ready.fn.call(this);
         } else {
               vrv._ready.r = true;
         }
    }
    if (options && options.constructor == Object) {
        vrv._init = options;
    }
    // options.success();
};


vrv.ready = function (fn) {
    if (typeof fn == 'function') {
        if (vrv._ready.r) {
            fn.call(this);
        } else {
            vrv._ready.fn = fn;
        }
    }
};