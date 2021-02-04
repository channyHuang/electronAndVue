<template>
  <div id="contextmenu" class="contextmenu">
    <div class="contextmenu__item" @click="setting()">设置</div>
    <div class="contextmenu__item" @click="aboutMe()">关于</div>
    <div class="contextmenu__item" @click="toolBox()">工具箱</div>
  </div>
</template>

<script>
export default {
  name: "index",
  data () {
    return {
    }
  },
  methods: {
    init (event) {
      let menu = document.querySelector('#contextmenu')
      menu.style.top = event.clientY + (document.body.clientHeight - event.clientY < 150 ? -150 : -10) + 'px'
      menu.style.left = event.clientX + (document.body.clientWidth - event.clientX < 100 ? -100 : 0) + 'px'
      document.addEventListener('click', this.foo)
    },
    foo () {
      this.$emit('foo')
    },
    setting () {
      this.$emit('setting')
    },
    aboutMe () {
      this.$emit('aboutMe')
    },
    toolBox () {
      this.$emit('toolBox')
    },
  }
}
</script>

<style scoped>
  .contextmenu__item {
    display: block;
    line-height: 34px;
    text-align: center;
  }
  .contextmenu__item:not(:last-child) {
    border-bottom: 1px solid rgba(64,158,255,.2);
  }
  .contextmenu {
    position: absolute;
    background-color: #ecf5ff;
    width: 100px;
    /*height: 106px;*/
    font-size: 12px;
    color: #409EFF;
    border-radius: 4px;
    -webkit-box-sizing: border-box;
    box-sizing: border-box;
    border: 1px solid rgba(64,158,255,.2);
    white-space: nowrap;
    z-index: 1000;
  }
  .contextmenu__item:hover {
    cursor: pointer;
    background: #66b1ff;
    border-color: #66b1ff;
    color: #fff;
  }
</style>
