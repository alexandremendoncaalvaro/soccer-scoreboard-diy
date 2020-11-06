const parentFixed = document.querySelector('#fixed-color-picker')
const parentFixed = document.querySelector('#color-picker-cont')
// const inputLedColor = document.querySelector('#input-led-color')

pickerFixed = new Picker({
    parent: parentFixed,
    popup: false,
    alpha: false,
    editor: true,
    color: 'white',
    onChange: function (color) {
        parentFixed.style.backgroundColor = color.rgbaString
        // inputLedColor.textContent = color.hex.substring(0, 7)
    },
})