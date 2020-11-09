const includeHtml = (personalizedAttribute) => {
    return new Promise((resolve, reject) => {
        const path = `./${personalizedAttribute}.html`
        const ajax = new XMLHttpRequest()
        ajax.open('GET', path, true)
        ajax.send()
        ajax.onload = (e) => {
            const htmlPlace = document.querySelector(`.include-${personalizedAttribute}`)
            htmlPlace.outerHTML = ajax.responseText
            resolve()
        }
    })
}

const includeAllHtml = (personalizedAttributes, callback) => {
    const allHtml = personalizedAttributes.map(includeHtml)
    Promise.all(allHtml).then(callback)
}