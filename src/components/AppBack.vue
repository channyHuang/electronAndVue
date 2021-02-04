<template>
  <div id="AppBack">
    <div align="right">
      <el-image
        :src="require('../assets/back.png')"
        @click="back"/>
    </div>
  </div>
</template>

<script>

export default {
  computed: {
  },
  methods: {
    back () {
      this.$router.back(-1)
      console.log("back")
    },
  },
  components: {
  }
}
</script>

<style lang="scss" scoped>
.app-header {
  width: 100%;
  height: 36px;
  -webkit-user-select: none;
  -webkit-app-region: drag;
  position: relative;
  display: flex;
  justify-content: space-between;

  > *:not(.app-title) {
    -webkit-app-region: no-drag;
  }

  .app-title {
    position: absolute;
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
  }
}
</style>
