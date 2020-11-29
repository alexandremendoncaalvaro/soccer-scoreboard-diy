const toggleMobileMenu = () => {
  const navMobile = document.getElementById("navMobile")
  if (navMobile.className.indexOf("w3-show") == -1) {
    navMobile.className += " w3-show"
  } else {
    navMobile.className = navMobile.className.replace(" w3-show", "")
  }
}
