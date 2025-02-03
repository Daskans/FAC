<script setup lang="ts">

import { ref } from 'vue'
import { getImageList, downloadImage } from './http-api';
import type { Image_t, imageElement } from './http-api';


const imageList = ref(<Image_t[]>([]));

const retrieveImageList = async () => {
  try {
    const response = await getImageList();
    imageList.value = response?.value ?? [];
  } catch (error) {
    console.error(error);
  }
}

const viewImage = async (id: number) => {
  console.log("Image ID => ",id);
  const image = await downloadImage(id);
}

</script>

<template>
    <div>
        <div class="container">
            <button @click="retrieveImageList()">Show Image Gallery</button>
        </div>
        <div class="gallery">
            <div v-for="image in imageList" :key="image.id" class="galleryImage" @click="viewImage(image.id)">
                <img :src="`/images/${image.id}`" :alt="image.name"/>
            </div>
        </div>
    </div>
</template>

<style scoped>

.gallery {
    display: flex;
    flex-wrap: wrap;
    justify-content: center;
    background-color: rgb(123, 135, 145);
    border: 5px solid rgb(79, 91, 92);
}

.galleryImage {
    display: inline-block;
    margin: 5px;
    margin-top: 20px;
    border: 2px solid rgb(59, 59, 59);
}

img {
    width: 200px;
    height: auto;
}

</style>