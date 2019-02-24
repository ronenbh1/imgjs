var remote = require('electron').remote;
var fs = remote.require('fs');
const sharp = require('sharp');

const image_loader = require('./build/Release/image_loader');
//console.log(image_loader.hello());
const image_buffer = Buffer.alloc(100000,0)
image_loader.get_image(image_buffer, 1000000)
console.time("sharp")
sharp(image_buffer)
    .normalise()
    .toBuffer()
    .then( data => {
        var _img = data.toString('base64');
        var _out = '<img src="data:image/png;base64,' + _img + '" />';
        var _target = document.getElementById('image_container');
        _target.insertAdjacentHTML('beforeend', _out);
    })
    .catch( err => {
        console.log(err);
    });												
 
console.timeEnd("sharp")
