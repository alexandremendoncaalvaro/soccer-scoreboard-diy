const post = (url, data) => {
    var ajax = new XMLHttpRequest();

    ajax.open("POST", url, true);
    ajax.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

    ajax.send(JSON.stringify(data));

    ajax.onreadystatechange = function () {

        if (ajax.readyState == 4 && ajax.status == 200) {

            var data = ajax.responseText;

            console.log(data);
        }
    }

    // return fetch(url, { method: 'POST', body: JSON.stringify(data) })

}

const hexToRgb = hex => {
    // Expand shorthand form (e.g. "03F") to full form (e.g. "0033FF")
    var shorthandRegex = /^#?([a-f\d])([a-f\d])([a-f\d])$/i
    hex = hex.replace(shorthandRegex, function (m, r, g, b) {
        return r + r + g + g + b + b
    })

    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex)
    return result ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16)
    } : null
}

const setColor = colorHex => {
    const color = hexToRgb(colorHex)
    post('/color', color)
}

// export { setColor }