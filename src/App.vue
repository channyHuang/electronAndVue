<template>
  <div id="app">
    <AppHeader />
    <router-view>
      <div id="app-content">
        <div id="nav">
          <router-link to="/">Home</router-link>
          <router-link to="/about">about</router-link>
        </div>
      </div>   
    </router-view>
  </div>
</template>

<script>

export default {
  name: 'app',
  data () {
    return {

    }
  }
}
</script>

<style lang="scss" scoped>
#app {
  height: 100%;
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  display: flex;
  flex-direction: column;

  #nav {
    padding: 30px;
    a {
      font-weight: bold;
      color: #2c3e50;
      &.router-link-exact-active {
        color: #42b983;
      }
    }
  }

  #app-content {
    overflow: auto;
    flex: 1;
  }
}
</style>
