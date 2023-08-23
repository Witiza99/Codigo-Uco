function updateImageDisplay() {
  while(preview.firstChild) {
    preview.removeChild(preview.firstChild);
  }

  var curFiles = input.files;
  if(curFiles.length === 0) {
    var para = document.createElement('p');
    para.textContent = 'No hay archivos subidos';
    preview.appendChild(para);
  } else {
    var list = document.createElement('ol');
    preview.appendChild(list);
    for(var i = 0; i < curFiles.length; i++) {
      var listItem = document.createElement('li');
      var para = document.createElement('p');
      if(validFileType(curFiles[i])) {
        para.textContent = 'File name ' + curFiles[i].name + ', file size ' + returnFileSize(curFiles[i].size) + '.';
        var image = document.createElement('img');
        image.src = window.URL.createObjectURL(curFiles[i]);

        listItem.appendChild(image);
        listItem.appendChild(para);

      } else {
        para.textContent = 'File name ' + curFiles[i].name + ': Not a valid file type. Update your selection.';
        listItem.appendChild(para);
      }

      list.appendChild(listItem);
    }
  }
}

var fileTypes = [
  'image/jpeg',
  'image/pjpeg',
  'image/png'
]

function validFileType(file) {
  for(var i = 0; i < fileTypes.length; i++) {
    if(file.type === fileTypes[i]) {
      return true;
    }
  }

  return false;
}

function returnFileSize(number) {
  if(number < 1024) {
    return number + 'bytes';
  } else if(number >= 1024 && number < 1048576) {
    return (number/1024).toFixed(1) + 'KB';
  } else if(number >= 1048576) {
    return (number/1048576).toFixed(1) + 'MB';
  }
}

function validarTitulo(inp){
  if(inp== "")return "No se introdujo T&iacutetulo\n";
  else if(inp.length< 5)return "T&iacutetulo demasiado corto\n";
  else if(inp.length> 30)return "T&iacutetulo demasiado largo\n";
  else if(/[^a-zA-Z0-9_-]/.test(inp))return "Car&aacutecteres inv&aacutelidos en T&iacutetulo\n";
  else return "";
}

function validarDescripcion_breve(inp){
  if(inp== "")return "No se introdujo Descripci&oacuten breve\n";
  else if(inp.length< 150)return "Descripci&oacuten breve demasiado larga\n";
  else if(/[^a-zA-Z0-9_-]/.test(inp))return "Car&aacutecteres inv&aacutelidos en Descripci&oacuten breve\n";
  else return "";

}

function validarDescripcion_completa(inp){
  if(inp== "")return "No se introdujo Descripci&oacuten completa\n";
  else if(inp.length< 700)return "Descripci&oacuten completa demasiado larga\n";
  else if(/[^a-zA-Z0-9_-]/.test(inp))return "Car&aacutecteres inv&aacutelidos en Descripci&oacuten completa\n";
  else return "";
}

function validarParticipantes(inp){
  if(inp== "")return "No se introdujeron participantes\n";
  else if(inp.length<300)return "Se ha excedido en el n&uacutemero de caracteres\n";
  else if(/[^a-zA-Z0-9_-]/.test(inp))return "Car&aacutecteres inv&aacutelidos usados en los participantes\n";
  else return "";
}

function validarPagina_Web(inp){
  if(inp== "")return "No se introdujo p&aacutegina web\n";
  else if(inp.length<150)return "Se ha excedido en el n&uacutemero de car&aacutecteres\n";
  else if(/[^a-zA-Z0-9\.\@\_\/\-]/.test(inp))return "Car&aacutecteres inv&aacutelidos para direccion de p&aacutegina web\n";
  else return "";
}
function validarBusqueda(inp){
  if(inp== "")return "No se introdujo p&aacutegina web\n";
  else if(/[^a-zA-Z0-9\.\_\/\-]/.test(inp))return "Car&aacutecteres inv&aacutelidos para buscar\n";
  else return "";
}