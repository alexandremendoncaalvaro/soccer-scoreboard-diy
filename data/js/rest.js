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
}