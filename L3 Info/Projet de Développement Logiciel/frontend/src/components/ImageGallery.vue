<script setup lang="ts">

import { ref } from 'vue'
import axios from 'axios';
import downloadImage from './ImageSingletonHandler.vue';
import images from './ImageSingletonHandler.vue';

const getImageList = async () => {
}

</script>

<template>
    <div>
        <ul>
            <div class="container">
                <button @click="getImageList()">Show Image Gallery</button>
            </div>
        </ul>
    </div>
</template>

<style scoped>

.container {
  display: flex;
  justify-content: center;
  align-items: center;
  margin: 20px;
}

button {
  background-color: #9499be;
  color: white;
  padding: 10px;
  border-radius: 5px;
  cursor: pointer;
}

</style>