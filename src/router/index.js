import Vue from 'vue'
import Router from 'vue-router'
// import AppEmpty from '@/components/AppEmpty'
import Error from '@/views/Error'

Vue.use(Router)

const router = new Router({
  mode: 'hash',
  base: process.env.BASE_URL,
  fallback: false,
  routes: [
    {
      path: '/',
      name: 'home',
      component: () => import(/* webpackChunkName: "home" */ '@/views/Home.vue'),
      meta: {
        title: '主页',
      }
    },
    {
      path: '/about',
      name: 'about',
      component: () => import(/* webpackChunkName: "about" */ '@/views/About.vue'),
    },
	  {
      path: '/ToolBoxPage',
      name: 'ToolBoxPage',
      component: () => import(/* webpackChunkName: "ToolBoxPage" */ '@/views/ToolBoxPage.vue'),
      meta: {
        title: '工具箱',
      }
    },
    {
      path: '/ScannerPage',
      name: 'ScannerPage',
      component: () => import(/* webpackChunkName: "ScannerPage" */ '@/views/ScannerPage.vue'),
      meta: {
        title: '扫描',
      }
    },
    {
      path: '*',
      name: 'error',
      component: Error
    }
  ]
})

export default router
