<script setup lang="ts">
import { ref } from 'vue'
import axios from 'axios';
import { getImageList, imageElement, images, downloadImage, selectedImage } from './http-api';

defineProps<{ msg: string }>()
const selectedFile = ref<File | null>(null);



const submitFile = async () => {
  if (selectedFile.value) {
    const formData = new FormData();
    formData.append('file', selectedFile.value);
    try {
      const response = await axios.post('/images', formData, {
        headers: {
          'Content-Type': 'multipart/form-data'
        }
      });
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  }
}

const handleFileUpload = (event: Event) => {
  const target = event.target as HTMLInputElement;
  if (target.files && target.files.length > 0) {
    selectedFile.value = target.files[0];
  }
}

</script>

<template>
  <h1>{{ msg }}</h1>

  <button @click="getImageList()">lézimaj</button>
  <div>
    <select v-model = "selectedImage">
      <option v-for="image in images" :key="image.id" :value="image.id">
        {{ image.name }}
      </option>
    </select>
  </div>
  <div>
    <button @click="downloadImage(-1)">Download</button>
  </div>
  <div class = "imageContainer">
    <img ref="imageElement" class = "mainImage" />
  </div>
  <div class="container">
    <div>
      <h2>Single File</h2>
      <hr/>
      <label>File
        <input type="file" @change="handleFileUpload"/>
      </label>
      <br>
      <button v-on:click="submitFile()">Submit</button>
    </div>
  </div>
</template>

<style scoped>
.read-the-docs {
  color: #414040;
}

button {
  background-color: #9499be;
  color: white;
  padding: 10px 20px;
  border-radius: 5px;
  cursor: pointer;
}

select {
  margin-top: 20px;
}

.imageContainer {
  margin-top: 20px;
}

.mainImage {
  max-width: 100%;
  height: auto;
}

.container {
  margin-top: 20px;
  display: flex;
  gap: 10px;
  align-items: center;
  justify-content: center;
}

input[type="file"] {
  padding: 10px;
}

</style>
