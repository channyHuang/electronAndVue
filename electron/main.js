const { app, BrowserWindow, ipcMain } = require("electron");
const ForNodeAddOn = require("./build/Release/ForNodeAddOn");

const fs = require("fs");
function reloadTheWin(win) {
  fs.watch("./dist", event => {
    if (event == "change") {
        console.log('updating')
      win.reload();
    }
  });
}
function createWindow() {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true,
      preload: __dirname + '/ipc.js'
    }
  });

  win.loadFile(__dirname + "./dist/index.html");
  reloadTheWin(win);
}

app.whenReady().then(createWindow);

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") {
    app.quit();
  }
});
app.on("activate", () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});

let gEvent;
function loginCallbackFunc(sMsg, nSeq) {
  console.log('loginCallbackFunc in main ' + sMsg + " " + nSeq);
  gEvent.sender.send('loginCallback', sMsg, nSeq);
}

ipcMain.on("CallJsSendToMain", (event, args) => {
  event.sender.send("CallJsSendToMainb", "send callback to vue " + args);
});
ipcMain.on("CallJsSendToMainSync", (event, args) => {
  event.returnValue = ForNodeAddOn.FunParamVoidReturnValid();
});
ipcMain.on("CallJsSendToDll", (event, args) => {
  console.log('CallJsSendToDll in main');
  ForNodeAddOn.Init();
  ForNodeAddOn.FuncSetCallback(loginCallbackFunc);
});
ipcMain.on("callLoginInDll", (event, args1, args2) => {
  console.log('callLoginInDll in main');
  gEvent = event;
  ForNodeAddOn.FunRequestNetworkAndCallback(args1, args2);
});
