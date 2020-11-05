import { toggleMobileMenu } from './menu.mjs'
import { includeAllHtml } from './dynamic-load.mjs'

const dynamicLoad = () => {
    const afterLoad = () => {
        document.querySelector('#menu-button').addEventListener('click', toggleMobileMenu)
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