<template>
  <div id="home">
    <h1>Hello World!</h1>
    <p>
      We are using node, chrome, electron and vue
    </p>
    <div id="robot">
      <el-image class="el-image"
        :src="require('../assets/robot.png')"
        :data="imageData"
        @contextmenu="contextmenu">
      </el-image>
    </div>
    <context-button v-if="menuVisible" @foo="foo" ref="contextbutton" @setting="setting" @aboutMe="aboutMe" @toolBox="toolBox"></context-button>
  </div>
</template>

<script>
// @ is an alias to /src
import contextButton from '@/components/contextMenuInMainPage'

export default {
  name: 'home',
  data () {
    return {
      imageData: [],
      menuVisible: false
    }
  },
  components: {
    contextButton
  },
  computed: {
  },
  methods: {
    contextmenu () {
      this.menuVisible = true
      event.preventDefault()
      this.$nextTick(() => {
        this.$refs.contextbutton.init(event)
      })
    },
    foo () {
      this.menuVisible = false
      document.removeEventListener('click', this.foo)
    },
    setting () {
      this.menuVisible = false
    },
    aboutMe () {
      this.menuVisible = false
      this.$router.push({ name: 'about' })
    },
    toolBox () {
      this.menuVisible = false
      this.$router.push({ name: 'ToolBoxPage' })
    }
  }
}
</script>

<style lang="scss" scoped>
#home {
  height: 100%;
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  display: flex;
  flex-direction: column;

  #robot {
    position: fixed;
    right: 10px;
    bottom: 10px;
  }
  #contextmenu {
    margin: 0;
    background: #fff;
    z-index: 3000;
    position: absolute;
    list-style-type: none;
    padding: 5px 0;
    border-radius: 4px;
    font-size: 12px;
    font-weight: 400;
    color: #333;
    box-shadow: 2px 2px 3px 0 rgba(0, 0, 0, 0.3);
    li {
      margin: 0;
      padding: 7px 16px;
      cursor: pointer;
      &:hover {
       background: #eee;
      }
    }
  }
}
</style>
