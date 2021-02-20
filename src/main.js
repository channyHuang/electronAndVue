import Vue from "vue";
import App from "./App.vue";
import router from "./router";
import store from "./store";
import ElementUI from 'element-ui';
import 'element-ui/lib/theme-chalk/index.css';

Vue.config.productionTip = false;
Vue.use(ElementUI);

Vue.directive('title', {
  inserted: function (el) {
    document.title = el.dataset.title
  }
})

router.beforeEach((to, from, next) => {
  window.document.title = to.meta.title == undefined?'默认标题':to.meta.title
  next();
})

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount("#app");
