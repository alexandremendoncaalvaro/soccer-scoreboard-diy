const dynamicLoadHtmlContent = () => {
  const afterLoad = () => {
    document
      .querySelector("#menu-button")
      .addEventListener("click", toggleMobileMenu)
  }

  const htmlList = Array.from(
    document.querySelectorAll(`[class*='dynamic-load-']`)
  ).map((e) => e.className.replace("dynamic-load-", ""))
  dynamicLoadAllHtml(htmlList, afterLoad)
}

const documentReady = () => {
  dynamicLoadHtmlContent()
}

if (document.readyState !== "loading") {
  documentReady()
} else {
  document.addEventListener("DOMContentLoaded", documentReady)
}
