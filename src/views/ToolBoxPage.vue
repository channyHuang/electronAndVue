<template>
  <div id="ToolBoxPage">
    <AppBack />
    <div id="app-content">
      <h1>测试工具</h1>
      <el-button type="primary" @click="callJsInVue">调用js</el-button>
      <el-button type="primary" @click="scanner">跳转到新窗口</el-button>
      <el-button type="primary">调用c++的dll</el-button>
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
      bIsScanning: false
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
      CallJsInVueClass.CallJsSendToMainSync();
    },
    back () {
      this.$router.back(-1)
    }
  }
}

</script>
