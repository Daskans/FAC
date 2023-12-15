// EXO 1
titrePage = document.querySelector('h1'); 
// EXO 3
titrePage.style.color = 'red';
// EXO 4
titrePage.align = 'center';
// EXO 5
images = document.querySelectorAll('img');
// EXO 8
images.forEach((image) => image.style.border = 'yellow 2px solid');
// EXO 10
bouton = document.querySelector('button');
// EXO 12
display = 'block';
bouton.addEventListener('click', () => {
	if (display=='block') {
		images.forEach((image) => image.style.display = 'inline');
		display = 'inline';
	} else if (display=='inline') {
		images.forEach((image) => image.style.display = 'block');
		display = 'block';
	}
});
// EXO 13
//window.addEventListener("scroll",() => console.log('scroll'))
// EXO 14
//murImages = document.getElementById('mur-images');
//nouvelleImage = document.createElement('img');
//nouvelleImage.src = 'public/image16_small.jpg';
//murImages.appendChild(nouvelleImage);
// EXO 15
window.addEventListener("scroll",() => {
    murImages = document.getElementById('mur-images');
    nouvelleImage = document.createElement('img');
    nouvelleImage.src = 'public/image12_small.jpg';
    murImages.appendChild(nouvelleImage);
});