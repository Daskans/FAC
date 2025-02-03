<script setup lang="ts">
import HelloWorld from './components/ImageSingletonHandler.vue'
import HelloWorld2 from './components/ImageGallery.vue'
</script>

<template>
  <div>
    <a href="https://vite.dev" target="_blank">
      <img src="/vite.svg" class="logo" alt="Vite logo" />
    </a>
    <a href="https://vuejs.org/" target="_blank">
      <img src="./assets/vue.svg" class="logo vue" alt="Vue logo" />
    </a>
  </div>
  <div class="container_1">
    <HelloWorld msg="Vite + Vue" />
  </div>
  <div class="container_2">
    <HelloWorld2/>
  </div>
</template>

<style scoped>
.logo {
  height: 6em;
  padding: 1.5em;
  will-change: filter;
  transition: filter 300ms;
}
.logo:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}
.logo.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}

.container_1 {
  margin-top: 20px;
  display: block;
  justify-content: center;
}

.container_2 {
  margin-top: 20px;
  display: block;
  justify-content: center;
}

</style>
