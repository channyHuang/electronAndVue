const CallJsInVueClass = {
    CallJsFunction:function(){
      console.log('CallJsFunction be called in callJsFunction.js ');
    },
    CallJsSendToMain:function(){
      console.log('CallJsSendToMain be called in callJsFunction.js ');
      window.ipcRenderer.send('CallJsSendToMain', 'hello from callJsInVue.js');
      window.ipcRenderer.once('CallJsSendToMainb', (event, args) => {
        console.log('CallJsSendToMain received back in callJsFunction.js ' + args);
      });
    },
    CallJsSendToMainSync:function(){
      var res = window.ipcRenderer.sendSync('CallJsSendToMainSync');
      return res;
    }
};

module.exports = CallJsInVueClass;