var remote = require('electron').remote;
var fs = remote.require('fs');
const sharp = require('sharp');

const image_loader = require('./build/Release/image_loader');
console.log(image_loader.hello());

console.time("sharp")
sharp('test/greymen.png')
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
