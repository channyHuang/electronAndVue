<template>
  <div id="ScannerPage">
    <div id="app-content" align="left" :style="{margin: '30px'}">
      <p>正在运行快速扫描...</p>
      <p>已扫描时间：{{ sUsedTime }}</p>
      <p>0 个文件已扫描</p>
      <p>正在扫描文件：</p>
      <el-progress type="line" :percentage="10"></el-progress>
      <el-button type="primary" @click="cancel">取消</el-button>
      <p>你可以在我们扫描设备时继续工作</p>
    </div>
  </div>
</template>

<script>

export default {
  name: 'ScannerPage',
  data () {
    return {
      nPercentage: 10,
      bIsScanning: false,
      timer: null,
      tStartTime: null,
      tCurTime: null,
      sUsedTime: '0'
    }
  },
  components: {
  },
  computed: {
  },
  watch: {
    tCurTime: function (val) {
      var diff = this.tStartTime.getTime - val
      this.sUsedTime = Math.floor(diff / (3600 * 1000)) + '时'
    }
  },
  methods: {
    scantimer () {
      if (this.timer == null) {
        this.timer = setInterval(() => {
          this.tCurTime = new Date()
        }, 1000)
      }
    },
    scanner () {
      this.bIsScanning = true
      let routeData = this.$router.resolve({ path: '/About' })
      window.open(routeData.href, '_blank')
    },
    cancel () {
      this.bIsScanning = false
    }
  },
  created: function () {
    this.getFamilyBase_info()
    clearInterval(this.timer)
    this.timer = null
    this.scantimer()
    this.tStartTime = new Date()
  },
  destroyed: function () {
    clearInterval(this.timer)
    this.timer = null
  }
}

</script>
