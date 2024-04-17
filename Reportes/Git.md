# COMANDOS GIT

Durante esta practica de laboratorio se desarrollaron conocimientos sobre el empleo de comandos Git desde el uso de una terminal de comandos.

### Descrubiendo la terminal.
##### Se nos mostraron comandos basicos que se emplean en la terminal de comandos, como ls, ls -a, ls -tree, cd, cd ., cd .., pwd  

![](Imagenes/Imagen1.png)

### Generar y subir repositorio
##### Una vez terminado el entendimiento de los comandos basicos de la linea de comandos iniciamos con el manejo de los comandos git.

##### Para ello creamos una carpeta y dentro de ella la inicializamos con el comando git init para inicializar el repositorio. 

![](Imagenes/Imagen2.png)

##### Posterior a esto visualizamos los archivos dentro de las carpetas que estan o no añadidos al repositorio con el comando git status
![](Imagenes/Imagen3.png)

##### Ahora para a añadir los archivos dentro del documento al repositorio utilizamos el comando git add direccion del archivo
![](Imagenes/Imagen4.png)

##### verificamos con el comando git status para ver que ya se añadieron los archivos al repositorio local
![](Imagenes/Imagen5.png)

##### Ahora agregamos un comentario con el comando git commit -m "Comentario"

![](Imagenes/Imagen6.png)

##### Para subir un este repositorio a github primeramente debemos crear un repositorio en GitHub para posteriormente enlazarlo con el comando git remote add origin [codigo ssh de su repositorio]
![](Imagenes/Imagen7.png)

##### Y para terminar agregando este comando a nuestro repositorio de Github debemos usar el comando Git push -u origin master
![](Imagenes/Imagen8.png)


