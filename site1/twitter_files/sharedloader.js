(window.webpackJsonp=window.webpackJsonp||[]).push([[7],{"07FG":function(e,t,n){"use strict";n.d(t,"a",(function(){return i}));var r=n("cnVF"),i=function(e){return e===r.B}},"2Aal":function(e,t,n){"use strict";n.d(t,"a",(function(){return y})),n.d(t,"b",(function(){return x})),n.d(t,"c",(function(){return I})),n.d(t,"d",(function(){return C})),n.d(t,"e",(function(){return T})),n.d(t,"f",(function(){return A}));n("z84I");var r=n("ERkP"),i=n.n(r),a=n("3XMw"),o=n.n(a),c=n("TIdA"),u=n("A91F"),s=n("rHpw"),d=n("oSwX"),l=n("9Xij"),f=n("Znyr"),p=n("aWyx"),m=n("U+bB"),v=n("MWbm"),_=(n("uFXj"),s.a.create((function(e){return{circle:{borderRadius:e.borderRadii.infinite,overflow:"hidden"},container:{height:"auto",width:"100%"},itemAccessory:{top:-e.spacesPx.space24+e.spacesPx.space1,right:-e.spacesPx.space16-e.spacesPx.space1},userDecoration:{fontSize:e.fontSizes.subtext3,position:"absolute",backgroundColor:e.colors.gray100,marginLeft:e.spaces.space8,boxSizing:"border-box",width:e.spaces.space24,height:e.spaces.space24}}}))),h=s.a.create((function(e){return{container:{flexDirection:"row"},left:{flex:1},right:{flex:1,marginLeft:e.borderWidths.small,marginRight:"calc(-1 * ".concat(e.borderWidths.small,")")}}})),g=s.a.create((function(e){return{container:{flexDirection:"column"},top:{flex:1,marginBottom:e.borderWidths.small},bottom:{flex:1}}})),b=_,y=3,E=o.a.fd48249b,w=function(e){var t=e.left,n=e.right;return i.a.createElement(v.a,{style:h.container},i.a.createElement(v.a,{style:h.left},t),i.a.createElement(v.a,{style:h.right},n))},O=function(e){var t=e.bottom,n=e.top;return i.a.createElement(v.a,{style:g.container},i.a.createElement(v.a,{style:g.top},n),i.a.createElement(v.a,{style:g.bottom},t))},x=function(e){return e?i.a.createElement(c.a,{accessibilityLabel:"",aspectMode:u.a.SQUARE,backgroundColor:s.a.theme.colors.gray50,image:e,rounded:!0}):null},I=function(e,t){var n=e.length;return 0===n?null:1===n?S(e[0],t):i.a.createElement(v.a,{style:b.circle},j(e))},C=function(e){return e?i.a.createElement(m.a,{source:e}):null},j=function(e){var t=e.length,n=e.map((function(e,n){var r=2===t||3===t&&0===n?.5:1;return e.profile_image_url_https?i.a.createElement(v.a,{key:e.id_str,style:b.container},i.a.createElement(d.default,{aspectRatio:r,shape:"none",size:"custom",uri:e.profile_image_url_https})):null}));if(2===t)return i.a.createElement(l.a,{ratio:1},i.a.createElement(w,{left:n[1],right:n[0]}));var r=i.a.createElement(O,{bottom:n[2],top:n[1]}),a=n[0];return i.a.createElement(w,{left:r,right:a})},S=function(e,t){return e.profile_image_url_https?i.a.createElement(v.a,{key:e.id_str,style:b.container},i.a.createElement(d.default,{size:t||"xxLarge",uri:e.profile_image_url_https})):null},T=function(e,t,n){return n===p.a.GROUP?"/messages/".concat(e,"/participants"):n===p.a.ONE_TO_ONE?"/".concat(t):void 0},A=function(e){var t=e.badgeCount;return i.a.createElement(v.a,{style:b.itemAccessory},i.a.createElement(f.a,{accessibilityLiveRegion:"none",count:t,standalone:!0,style:b.userDecoration,textColor:"text",truncatedCountFormatter:function(){return""},unreadCountLabel:E,withTruncatedCount:!1}))}},"6M7t":function(e,t,n){"use strict";n.d(t,"a",(function(){return s}));var r=n("ERkP"),i=n.n(r),a=n("2Aal"),o=n("aI6n"),c=n("9Xij"),u=n("cm6r");function s(e){var t=e.avatar,n=e.avatarLink,r=e.badgeCount;return i.a.createElement(i.a.Fragment,null,i.a.createElement(c.a,{ratio:1},n?i.a.createElement(u.a,{interactiveStyles:null,link:n,testID:o.a.conversationAvatar},t):t),r?Object(a.f)({badgeCount:r}):null)}},AQOc:function(e,t,n){"use strict";n.d(t,"b",(function(){return _})),n.d(t,"a",(function(){return h}));var r=n("yiKp"),i=n.n(r),a=n("m3Bd"),o=n.n(a),c=(n("z84I"),n("Blm6"),n("lTEL"),n("7x/C"),n("kYxP"),n("LW0h"),n("lnti")),u=n("aWyx"),s=n("Yatk"),d=["users"],l=["conversation_id","participants"],f=["conversation_id","participants","social_proof"],p={entries:{},entryIdsByConversationId:{},reactionsByMessageId:{}},m=function(){var e=arguments.length>0&&void 0!==arguments[0]?arguments[0]:[],t=arguments.length>1&&void 0!==arguments[1]?arguments[1]:{};return e.map((function(e){return i()(i()({},e),{},{user:Object(s.a)(t[e.user_id])||{created_at:"",description:"",entities:{},followed_by:!1,followers_count:0,following:!1,friends_count:0,id:parseInt(e.user_id,10),id_str:e.user_id,name:"",profile_image_url_https:"",protected:!1,screen_name:"",verified:!1}})}))};function v(e,t){var n=t.entries;return(t.entryIdsByConversationId[e]||[]).map((function(e){return n[e]&&n[e].data})).filter(Boolean)}var _=function(e){var t=arguments.length>1&&void 0!==arguments[1]?arguments[1]:p,n=arguments.length>2?arguments[2]:void 0,r=e.conversation_id,a=e.participants,c=o()(e,l);return i()(i()({conversation_id:r},c),{},{entries:t.entryIdsByConversationId[r]||[],participants:m(a,n)})},h=function(e,t,n){var r=e.conversation_id,a=e.participants,l=e.social_proof,p=o()(e,f),_=i()(i()({conversation_id:r},p),{},{entries:v(r,t),participants:m(a,n),social_proof:void 0});return l&&(_.social_proof=function(){var e=arguments.length>1&&void 0!==arguments[1]?arguments[1]:{};return(arguments.length>0&&void 0!==arguments[0]?arguments[0]:[]).map((function(t){if(t.proof_type===u.d.MUTUAL_FRIENDS){var n=t.users,r=o()(t,d);return i()(i()({},r),{},{users:Object(c.a)(n.map((function(t){return Object(s.a)(e[t])})))})}return t}))}(l,n)),_}},CDB5:function(e,t,n){"use strict";n.d(t,"m",(function(){return C})),n.d(t,"l",(function(){return S})),n.d(t,"f",(function(){return A})),n.d(t,"d",(function(){return M})),n.d(t,"g",(function(){return U})),n.d(t,"e",(function(){return N})),n.d(t,"i",(function(){return k})),n.d(t,"j",(function(){return L})),n.d(t,"k",(function(){return z})),n.d(t,"h",(function(){return G})),n.d(t,"a",(function(){return V})),n.d(t,"b",(function(){return F})),n.d(t,"c",(function(){return Y}));var r=n("RhWx"),i=n.n(r),a=n("ddV6"),o=n.n(a),c=n("KEM+"),u=n.n(c),s=n("yiKp"),d=n.n(s),l=(n("TJCb"),n("7x/C"),n("DZ+c"),n("7xRU"),n("lTEL"),n("JtPf"),n("87if"),n("kYxP"),n("2G9S"),n("1IsZ"),n("AspN")),f=n("xPna"),p=n("oEOe"),m=n("xCUF"),v=n("ude7"),_=n("07FG"),h=n("Ssj5"),g=n("fEA7"),b=n.n(g),y=n("uKEd"),E=n("lnti"),w=n("/NU0"),O="dmComposer",x={};var I=function(e){var t=e.conversation_id,n=e.id,r=e.localMediaId,i=e.recipient_ids,a=e.sender_id,o=e.text,c=e.attachment,u=void 0===c?{}:c,s=e.error,d=Date.now().toString();return{conversation_id:t,recipient_ids:i,error:s,id:n,is_draft:!0,message_data:{attachment:u,localMediaId:r,sender_id:a,text:o,time:d},type:"message",time:d}},C=function(e){return function(t,n,r){var a=r.api,c=e||{},u=c.senderId,s=c.cardUrl,h=c.conversationId,g=c.localMediaId,O=c.recipients,x=void 0===O?[]:O,C=c.requestId,j=void 0===C?b.a.v1():C,S=c.tweetAttachment,T=c.quickReply,A=c.text;t(Q(h));var R=n(),U=g||D(n(),h);null===U&&(U=[]);var P=l.k(R,U),N=o()(P,1)[0]||{},k=N.mediaFile,L=N.mediaMetadata,z=x.length>0&&x.join(","),W={};k&&k.isGif?W.extraInitParams="&media_category=dm_gif":k&&k.isVideo&&(W.extraInitParams="&media_category=dm_video");var V=l.p(U,W),B=[t(V)],F=(G(R,h)||{}).found_media_origin;return k&&k.isGif&&B.push(Object(v.a)(k)),Promise.all(B).then((function(n){var r=o()(n,2),c=o()(r[0],1)[0],v=r[1],g=(null==L?void 0:L.altText)||(null==L?void 0:L.defaultAltText)||"",b=!!g;return(c&&(F||b)?t(l.m(d()({media_id:c.uploadId,found_media_origin:F},!!b&&{alt_text:{text:g||""}}))):Promise.resolve()).then((function(){var n=(S||{}).id_str,r={};if(c){var o=c.mediaFile,l=void 0===o?{}:o,g={original_info:{width:l.width,height:l.height},sizes:[{h:l.height,w:l.width,resize:"fit"}]};l.isImage?r.photo=d()(d()({},g),{},{media_url_https:l.url}):l.isGif?r.animated_gif=d()(d()({},g),{},{media_url_https:v,type:"animated_gif"}):l.isVideo&&(r.video=d()(d()({},g),{},{media_url_https:l.url,type:"video"}))}else S&&(r.tweet={status:n});var b=(c||{}).uploadId,O=I({attachment:r,conversation_id:h,error:!1,id:j,localMediaId:null,recipient_ids:z,sender_id:u,text:A}),x=d()(d()(d()({},Object(_.a)(s)&&{card_uri:s}),{},{conversation_id:h},!n&&{media_id:b}),{},{recipient_ids:z,request_id:j,text:e.text,tweet_id:n});T&&(x["quick_reply_response[options][id]"]=T.id,x["quick_reply_response[options][selected_id]"]=T.selected_id);var C=Object(E.a)([H(h),{type:m.c.REQUEST},{type:"rweb/dmComposer/SEND_MESSAGE_REQUEST"},h&&Object(y.b)(h,j,O)]);return t(C),a.DirectMessages.sendMessage(x).then((function(n){var r=n.entities,a=r.cards,o=r.entries,c=r.tweets,u=r.users,s=n.result.conversations;Object(w.a)(U)&&t(Y(h,U));var d=Object(E.a)([{type:m.c.SUCCESS}].concat(i()(Object(f.a)({conversations:s,entries:o,users:u,tweets:c,cards:a})),[{type:"rweb/dmComposer/SEND_MESSAGE_SUCCESS"},h&&Object(y.j)(h,j,e),M(h)]));return t(d),Promise.resolve(Object.values(n.entities.entries)[0].conversation_id)}),(function(e){var n=I({attachment:r,conversation_id:h,error:!0,id:j,localMediaId:U,recipient_ids:z,sender_id:u,text:A}),i=Object(E.a)([{type:m.c.SUCCESS},{type:"rweb/dmComposer/SEND_MESSAGE_FAILURE"},h&&Object(y.b)(h,j,n)]);return t(i),Object(p.e)(t,e,"ACTION_SEND_DM")}))}),(function(e){return t($(h)),e.type="metadata",Promise.reject(e)}))}),(function(e){return t(Object(E.a)([Object(w.a)(U)&&Y(h,U),$(h)])),Promise.reject(e)}))}},j=function(e,t){return e.dmComposer[t]},S=function(e,t){var n=j(e,t);return n?n.text:null},T="rweb/dmComposer/SAVE_TEXT",A=function(e,t){return{type:T,conversationId:e,text:t}},R="rweb/dmComposer/REMOVE_TEXT",M=function(e){return{type:R,conversationId:e}},U=function(e,t){var n=j(e,t);return n?n.cardUrl:null},P="rweb/dmComposer/SAVE_CARD_URL",N=function(e,t){return{type:P,conversationId:e,cardUrl:t}},D=function(e,t){var n=j(e,t);return n&&void 0!==n.mediaId?n.mediaId:null},k=function(e,t){var n=l.k(e,D(e,t)||[]);return n.length>0?n[0]:null},L=function(e,t){var n=j(e,t);return!!n&&n.isUploading},z=function(e,t){return l.l(e,D(e,t)||0)},G=function(e,t){var n=j(e,t);return n&&n.gifMetadata?n.gifMetadata:null},W="rweb/dmComposer/ADD_MEDIA",V=function(e,t,n){return{payload:{isUploading:!1,mediaId:o()(t,1)[0],gifMetadata:n},type:W,conversationId:e}},B="rweb/dmComposer/CANCEL_UPLOAD",F=function(e){return{type:B,conversationId:e}},X="rweb/dmComposer/REMOVE_MEDIA",q=function(e){return{type:X,conversationId:e}},Y=function(e,t){return function(n){n(l.i(t)),n([F(e),q(e)])}},K="rweb/dmComposer/UPLOAD_REQUEST",Q=function(e){return{type:K,conversationId:e}},J="rweb/dmComposer/UPLOAD_SUCCESS",H=function(e){return{type:J,conversationId:e}},Z="rweb/dmComposer/UPLOAD_FAILURE",$=function(e){return{type:Z,conversationId:e}};h.a.register(u()({},O,(function(){var e=arguments.length>0&&void 0!==arguments[0]?arguments[0]:x,t=arguments.length>1?arguments[1]:void 0,n=t.conversationId||"new_group",r=e[n]||{cardUrl:null,gifMetadata:null,isUploading:!1,mediaId:null,text:null};switch(t.type){case W:return d()(d()({},e),{},u()({},n,d()(d()({},r),t.payload)));case K:return d()(d()({},e),{},u()({},n,d()(d()({},r),{},{isUploading:!0})));case B:return d()(d()({},e),{},u()({},n,d()(d()({},r),{},{isUploading:!1})));case Z:case J:case X:return d()(d()({},e),{},u()({},n,d()(d()({},r),{},{isUploading:!1,mediaId:null,gifMetadata:void 0})));case T:return d()(d()({},e),{},u()({},n,d()(d()({},r),{},{text:t.text})));case P:return d()(d()({},e),{},u()({},n,d()(d()({},r),{},{cardUrl:t.cardUrl})));case R:return d()(d()({},e),{},u()({},n,d()(d()({},r),{},{text:null})));default:return e}})))},OhSZ:function(e,t,n){"use strict";n.d(t,"a",(function(){return O}));var r=n("ddV6"),i=n.n(r),a=(n("z84I"),n("ho0z"),n("ERkP")),o=n.n(a),c=n("MMRb"),u=n("XnpN"),s=n("3XMw"),d=n.n(s),l="DMGroupConversationTitle",f=n("MWbm"),p=n("jV+4"),m=n("pjBI"),v=n("t62R"),_=n("rHpw"),h=n("X/yg"),g=n("p9G8"),b=d.a.cfd94063,y=d.a.b93ba92d,E=function(){var e=arguments.length>0&&void 0!==arguments[0]?arguments[0]:[];return e.map((function(e){return e.data}))},w=_.a.create((function(e){return{dmGroup:{display:"flex",flexDirection:"column"},highlightedTitle:{backgroundColor:e.colors.yellow400},messageSearchMiddot:{alignItems:"center"},messageSearchTitleContainer:{flexDirection:"row"},title:{maxWidth:"50%"}}})),O=function(e){var t=e.conversation,n=e.newConversationParticipants,r=e.perspective;if(t){if(t.type===c.CONVERSATION_TYPE.ONE_TO_ONE){var a=Object(u.a)(t,r).map((function(e){return e.user}));return i()(a,1)[0].name}return Object(g.a)(t,r)}var o=E(n);return Object(g.b)(o,r)};t.b=function(e){var t=e.conversation,n=e.highlightingTokens,r=void 0===n?null:n,a=e.isConversationSearchTitle,s=void 0!==a&&a,d=e.isMessageSearchTitle,_=void 0!==d&&d,O=e.newConversationParticipants,x=e.perspective,I=e.renderAvatarCell,C=e.renderTimestamp,j=e.textColor,S=void 0===j?"text":j,T=e.textSize,A=e.titleWeight,R=void 0===A?"bold":A,M=e.withParticipantsCount,U=void 0!==M&&M,P=e.withScreenName,N=void 0===P||P,D=e.withVDLRefresh,k=void 0!==D&&D;if(t){var L=C?C():null;if(t.type===c.CONVERSATION_TYPE.ONE_TO_ONE){var z=Object(u.a)(t,x).map((function(e){return e.user})),G=i()(z,1)[0],W=G.name,V=s?Object(h.i)(r,W):null,B=null!=V&&V.length?Object(h.f)(V,W):void 0,F=o.a.createElement(p.a,{color:S,isProtected:G.protected,isVerified:G.verified,name:W,nameSize:T,renderUserNameHighlights:B&&B,screenName:G.screen_name,weight:R,withLink:!1,withScreenName:N});return k&&!s||_?o.a.createElement(f.a,{style:w.messageSearchTitleContainer},_&&I?I():null,o.a.createElement(m.a,{style:_&&w.messageSearchMiddot},F,L)):F}var X=t.participants.length+(k?-1:0),q=Object(g.a)(t,x,s),Y=q?Object(h.i)(r,q):null,K=q&&null!=Y&&Y.length?Object(h.f)(Y,q):void 0;if(s)return o.a.createElement(m.a,{color:S},o.a.createElement(v.b,{color:S,numberOfLines:1,size:T,style:w.title,weight:R},K?K():q),k?null:o.a.createElement(v.b,{color:"gray700",numberOfLines:1,weight:"normal"},b({peopleCount:X})));var Q=o.a.createElement(v.b,{color:S,numberOfLines:1,size:T,testID:l,weight:R},Object(g.a)(t,x,s,k?2:void 0));return k&&!s||_?o.a.createElement(f.a,{style:[w.dmGroup,_&&w.messageSearchTitleContainer]},_&&I?I():null,o.a.createElement(m.a,{style:_&&w.messageSearchMiddot},Q,L),U&&o.a.createElement(v.b,{color:"gray700",numberOfLines:1,size:T},y({peopleCount:X}))):Q}var J=E(O);return o.a.createElement(v.b,{color:S,numberOfLines:1,size:T,weight:R},Object(g.b)(J,x))}},"X/yg":function(e,t,n){"use strict";n.d(t,"s",(function(){return g})),n.d(t,"r",(function(){return b})),n.d(t,"q",(function(){return y})),n.d(t,"n",(function(){return E})),n.d(t,"h",(function(){return w})),n.d(t,"f",(function(){return O})),n.d(t,"i",(function(){return x})),n.d(t,"c",(function(){return I})),n.d(t,"d",(function(){return C})),n.d(t,"l",(function(){return j})),n.d(t,"o",(function(){return S})),n.d(t,"p",(function(){return T})),n.d(t,"j",(function(){return A})),n.d(t,"m",(function(){return R})),n.d(t,"k",(function(){return M})),n.d(t,"g",(function(){return U})),n.d(t,"a",(function(){return P})),n.d(t,"b",(function(){return N})),n.d(t,"e",(function(){return D}));var r=n("yiKp"),i=n.n(r),a=(n("vrRf"),n("tQbP"),n("z84I"),n("LW0h"),n("7x/C"),n("vfdX"),n("ho0z"),n("CDB5")),o=n("ERkP"),c=n.n(o),u=n("XnpN"),s=n("gaV8"),d=n.n(s),l=n("AQ79"),f=n("s1N3"),p=n("lnti"),m=n("Myq3"),v=n("pHkl"),_=n("Q0VY"),h=n("FiRh"),g=function(e,t){return t.location&&t.location.state&&t.location.state.tweetAttachment},b=function(e,t){return t.location&&t.location.state&&t.location.state.participants},y=function(e,t){return t.location&&t.location.state&&t.location.state.isNewGroupConversation},E=function(e){return e&&Object(f.a)(e)},w=function(e,t){if(e&&t){var n=d()(e),r=t.toLowerCase().indexOf(e.toLowerCase());return{startIndex:r,endIndex:r+n}}return{startIndex:-1,endIndex:-1}},O=function(e,t){var n=_.a.plainTextParts(t);return function(){return c.a.createElement(c.a.Fragment,null,n.map((function(t,n){var r=t;return"text"===t.entityType?r=i()(i()({},t),{},{highlights:e,highlightType:"background"}):"emoji"===t.entityType&&(r=i()(i()({},t),{},{highlights:e})),c.a.createElement(h.b,{key:"".concat(n),part:r})})))}},x=function(e,t){var n=E(e),r=null==n?void 0:n.filter((function(e){return t&&-1!==t.toLowerCase().indexOf(e.toLowerCase())})),i=null!=r&&r.length?Object(p.a)(r.map((function(e){return function(e,t){if(e&&t){var n=d()(e),r=t.toLowerCase().indexOf(e.toLowerCase());return[r,r+n]}}(e,t)}))):void 0;return i&&null!=i&&i.length?i.sort((function(e,t){return e[0]-t[0]})):void 0},I=function(e){var t=e.message_data,n=v.h.UNKNOWN,r=t&&t.attachment||{};return r.tweet?n=v.h.TWEET:r.photo?n=v.h.PHOTO:r.animated_gif?n=v.h.GIF:r.video?n=r.video.audio_only?v.h.VOICE:v.h.VIDEO:r.card?n=v.h.CARD:null!=t&&t.text&&(n=v.h.TEXT),n};function C(e,t){return e.findIndex((function(e){return e.id===t}))}function j(e){return e===l.d.SECONDARY?v.g.REQUEST:e===l.d.TERTIARY?v.g.LOW_QUALITY:v.g.PRIMARY}function S(e){return e.isTrue("dm_voice_rendering_enabled")}function T(e,t){return!!(e&&e.video&&S(t))&&!!e.video.audio_only}function A(e,t,n,r){return{pathname:"/i/report/dm_conversation/".concat(e),state:{clientReferer:t,inboxType:r,scribeNamespace:n}}}function R(e,t){if(!e)return{name:"",screenName:"",idStr:""};var n=Object(u.a)(e,t).map((function(e){return e.user})),r=n&&n[0];return{name:r&&r.name||"",screenName:r&&r.screen_name||"",idStr:r&&r.id_str||""}}var M=function(e){return e===l.d.TERTIARY?"low_quality_timeline":e===l.d.SECONDARY?"requests_timeline":"inbox_timeline"},U=function(e){return e===l.d.TERTIARY?"/messages/requests/additional":e===l.d.SECONDARY?"/messages/requests":"/messages"},P=function(e){return function(){return a.b(e)}},N=function(e){return function(t){return a.c(e,t)}},D=function(e,t){var n=Object(m.a)(e,(function(e){return!!e.message_data&&(e.message_data&&e.message_data.recipient_id===t)}));return n&&n.message_data&&n.message_data.quick_reply&&n.message_data.quick_reply&&"options"===n.message_data.quick_reply.type?n.message_data.quick_reply:void 0}},XnpN:function(e,t,n){"use strict";var r=n("RhWx"),i=n.n(r),a=n("ddV6"),o=n.n(a),c=(n("2G9S"),n("tQbP"),n("aWyx")),u=(n("6U7i"),n("LW0h"),n("7x/C"),n("z84I"),n("t0aI")),s=function(){var e=arguments.length>0&&void 0!==arguments[0]?arguments[0]:0;return new Date(Number(e))},d=function(e,t){return s(e.join_time)-s(t.join_time)},l=function(e,t){var n=e.user,r=t.user;return Object(u.a)(n.id_str,r.id_str)},f=function(e){return function(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n];return function(e,n){return t.map((function(t){return t(e,n)})).filter((function(e){return!!e}))[0]||0}}(function(e){return function(t,n){var r=t.user,i=n.user;switch(e){case r.id_str:return-1;case i.id_str:return 1;default:return 0}}}(e),d,l)},p=n("VIKJ");t.a=function(e,t){var n=e.created_by_user_id,r=e.participants,a=e.type,u=Object(p.a)(r,(function(e){return e.user.id_str===t})),s=o()(u,2),d=s[0],l=s[1];return l.length?a===c.a.GROUP&&1===l.length?[].concat(i()(d),i()(l)):n?l.sort(f(n)):l:d}},Yatk:function(e,t,n){"use strict";n.d(t,"a",(function(){return r}));n("1t7P"),n("jQ/y"),n("ho0z");var r=function(e){if(e)return{blocking:e.blocking,can_dm:e.can_dm,can_media_tag:e.can_media_tag,created_at:e.created_at,description:e.description,entities:e.entities,followed_by:e.followed_by,followers_count:e.followers_count,following:e.following,friends_count:e.friends_count,id:e.id,id_str:e.id_str,name:e.name,profile_image_url_https:e.profile_image_url_https,protected:e.protected,screen_name:e.screen_name,verified:e.verified}}},aA19:function(e,t,n){"use strict";n("z84I"),n("M+/F");var r=n("ERkP"),i=n.n(r),a=n("6M7t"),o=n("XnpN"),c=n("2Aal");t.a=function(e){var t=e.conversation,n=e.perspective,r=e.size,u=e.withBadge;if(t){var s,d,l=t.avatar_image_https,f=Object(o.a)(t,n).map((function(e){return e.user})),p=f.slice(0,c.a).map((function(e){return{id_str:e.id_str,profile_image_url_https:e.profile_image_url_https,screen_name:e.screen_name}})),m=(null===(s=t.avatar)||void 0===s||null===(d=s.image)||void 0===d?void 0:d.original_info)||void 0,v=Object(c.b)(m)||Object(c.d)(l)||Object(c.c)(p,r),_=Object(c.e)(t.conversation_id,f[0].screen_name,t.type),h=u&&null!=t&&t.participants?t.participants.length-1:0;return v?i.a.createElement(a.a,{avatar:v,avatarLink:_,badgeCount:h}):null}return null}},aI6n:function(e,t,n){"use strict";t.a={conversationAvatar:"DM_Conversation_Avatar",newDM:"NewDM_Button",untrustedThumbnail:"DM_Untrusted_Thumbnail"}},kIAd:function(e,t,n){"use strict";n.d(t,"a",(function(){return i})),n.d(t,"b",(function(){return a}));var r=n("0vv5"),i=500,a={scoper:[{type:"dmUserSearch",regexp:/^[@＠]?(.*)|^$/,srcInputs:["compose_message"],scope:{result_type:"users",count:20}},{type:"username",regexp:/^[@＠](\w{1,20})/,srcInputs:["compose"],scope:{result_type:"users",count:20}},{type:"hashtag",regexp:n.n(r).a,srcInputs:["compose"],scope:{result_type:"topics",count:20}},{type:"topic",regexp:/(.+)/,srcInputs:["search_box"],scope:{result_type:"all"}},{type:"ttt",regexp:/(.+)/,srcInputs:["welcome_flow"],scope:{count:10,result_type:"topics,ttt"}}],WordBoundary:/[!'%&'()*+,\\\-./:;<=>?[\]^{|}~\s]|$/,WordEnd:/[^!'%&'()*+,\\\-./:;<=>?[\]^{|}~\s]+$/}},oEoC:function(e,t,n){"use strict";n.d(t,"e",(function(){return d})),n.d(t,"c",(function(){return l})),n.d(t,"b",(function(){return f})),n.d(t,"g",(function(){return p})),n.d(t,"a",(function(){return m})),n.d(t,"d",(function(){return v})),n.d(t,"f",(function(){return h}));var r=n("RhWx"),i=n.n(r),a=n("yiKp"),o=n.n(a),c=(n("hBpG"),n("7x/C"),n("vrRf"),n("KqXw"),n("WNMA"),n("M+/F"),n("LJOr"),n("tVqn"),n("jwue"),n("+oxZ"),n("z84I"),n("LW0h"),n("2G9S"),n("zTrU")),u=n("kIAd"),s=n("rHpw");function d(e,t){var n,r=u.b.scoper.find((function(r){if(-1!==r.srcInputs.indexOf(t))return n=e.match(r.regexp)})),i="";return n&&(i=n&&(1===n.length?n[0]:n[1])),r?o()(o()({},r.scope),{},{src:t,q:i}):null}function l(e,t){var n=t.slice(0,e),r=t.slice(e,t.length),i=n.search(u.b.WordEnd),a=i>=0?n.slice(i):"",o=r.search(u.b.WordBoundary),c=a+r.slice(0,o);return c.trim()?{start:i,end:e+o,word:c}:{start:-1,end:-1,word:""}}function f(){return"typeaheadFocus-".concat(Math.random())}function p(e){var t=e.altKey,n=e.ctrlKey,r=e.metaKey;return!(t||n||r)}function m(e,t){var n=[];e.forEach((function(e){var r=t.find((function(t){return t.id===e.id}));r&&r.data&&r.data.result_context?n.push(r):n.push(e)}));var r=n.map((function(e){return e.id})),a=t.filter((function(e){return r.indexOf(e.id)<0}));return[].concat(n,i()(a))}var v=Object(c.a)((function(e){return{bottom:0,paddingBottom:"calc(2.5 * ".concat(s.a.theme.spaces.space64,")"),position:"fixed",top:"calc(".concat(e,"px + ").concat(s.a.theme.spaces.space1,")"),transform:[{translate3d:"0,0,0"}]}})),_=0,h=function(){return"typeaheadDropdown-".concat(_+=1)}},p9G8:function(e,t,n){"use strict";n.d(t,"b",(function(){return m}));var r=n("ddV6"),i=n.n(r),a=(n("ho0z"),n("z84I"),n("LW0h"),n("7x/C"),n("M+/F"),n("Xrkv")),o=n("aWyx"),c=n("XnpN"),u=n("3XMw"),s=n.n(u),d=s.a.b5b7fb94,l=s.a.g755fcde,f=s.a.f6b1ff81,p=s.a.j652293d;t.a=function(e,t,n,r){var i=e.type,a=e.name,u=e.participants,s=void 0===u?{}:u;if(i===o.a.GROUP&&a)return a;if(s.length){if(i===o.a.GROUP&&n)return d;var l=Object(c.a)(e,t).map((function(e){return e.user}));return m(l,t,i,r)}};var m=function(){var e=arguments.length>0&&void 0!==arguments[0]?arguments[0]:[],t=arguments.length>1?arguments[1]:void 0,n=arguments.length>2&&void 0!==arguments[2]?arguments[2]:o.a.GROUP,r=arguments.length>3?arguments[3]:void 0,c=e.filter((function(e){return e.id_str!==t})).map((function(e){return e.name}));switch(c.length){case 0:return l;case 1:var u=i()(c,1),s=u[0];return n===o.a.GROUP?f({name:s}):s;default:var d=!0,m=r?c.slice(0,r):c,v=Object(a.a)(m,d),_=r?Math.max(c.length-r,0):0;return _>0?p({listOfParticipants:v,count:_}):v}}},ude7:function(e,t,n){"use strict";n.d(t,"a",(function(){return s}));n("7x/C"),n("JtPf");var r=n("A0bJ"),i=n("hJBK"),a=n("1auM"),o=1,c=2,u=3,s=function(e){if(Object(a.b)(e)){if(e.isGif){var t=e.height,n=e.img,s=e.orientation,d=e.width;return Object(i.b)(n,d,t,s).then((function(e){return Object(i.a)(e)}),(function(e){throw new r.a("Gif preview could not be generated",u)}))}var l=new r.a("The provided image must be a gif",c);return Promise.reject(l)}var f=new r.a("The provided file is not a valid image",o);return Promise.reject(f)}}}]);
//# sourceMappingURL=https://ton.local.twitter.com/responsive-web-internal/sourcemaps/client-web-legacy/shared~loader.DMDrawer~loader.Typeahead~bundle.Communities~bundle.DMRichTextCompose~bundle.Delegate~bundle.Lo.3e23db77.js.map