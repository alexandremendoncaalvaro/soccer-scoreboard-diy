// import { toggleMobileMenu } from './menu.js'
// import { includeAllHtml } from './dynamic-load.js'
// import { setColor } from './rest.js'

const dynamicLoad = () => {
    const afterLoad = () => {
        document.querySelector('#menu-button').addEventListener('click', toggleMobileMenu)
        document.querySelector('#led-color').addEventListener('input', e => {
            setColor(e.target.value)
        })
    }

    const htmlList = Array.from(document.querySelectorAll(`[class*='include-']`)).map(e => e.className.replace('include-', ''))
    includeAllHtml(htmlList, afterLoad)
}

const documentReady = () => {
    dynamicLoad()
}

if (document.readyState !== 'loading') {
    documentReady()
} else {
    document.addEventListener('DOMContentLoaded', documentReady)
}