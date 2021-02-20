<template>
  <div id="ToolBoxPage">
    <AppBack />
    <div id="app-content">
      <h1>测试工具</h1>
      <el-button type="primary" @click="callJsInVue">调用js</el-button>
      <el-button type="primary" @click="scanner">跳转到新窗口</el-button>
      <el-button type="primary" @click="callDllFunc">调用c++的dll设置回调</el-button>
      <el-button type="primary" @click="callLoginInDll">登录有回调</el-button>
    </div>
    <div>
      <el-tag>{{ sMessage }}</el-tag>
    </div>
  </div>
</template>

<script>
import AppBack from "@/components/AppBack"
import CallJsInVueClass from "@/callJsInVue.js"

export default {
  name: 'ToolBoxPage',
  data () {
    return {
      bIsScanning: false,
      sMessage: ''
    }
  },
  components: {
    AppBack
  },
  methods: {
    scanner () {
      this.bIsScanning = true
      let routeData = this.$router.resolve({ path: '/ScannerPage' })
      window.open(routeData.href, '_blank')
    },
    callJsInVue () {
      CallJsInVueClass.CallJsFunction();
      CallJsInVueClass.CallJsSendToMain();
      var res = CallJsInVueClass.CallJsSendToMainSync();
      console.log("callJsInVue return value in vue " + res.sResult);
      this.sMessage = res.sResult;
    },
    callDllFunc () {
      CallJsInVueClass.CallJsSendToDll();
    },
    callLoginInDll () {
      CallJsInVueClass.callLoginInDll();
    },
    back () {
      this.$router.back(-1)
    }
  }
}

</script>
