function httpGetAsync(theUrl, callback)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            callback(xmlHttp.responseText);
    }
    xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    xmlHttp.send(null);
}

function displayResponse(responseText)
{
    var response = $.parseJSON(responseText);
    $("#table").empty();

    var headRow = $("<tr></tr>");
    headRow.append($("<th></th>").text("Uhrenname"));
    headRow.append($("<th></th>").text("Absolutzeit"));
    headRow.append($("<th></th>").text("Datum"));
    headRow.append($("<th></th>").text("Zeit"));
    $("#table").append(headRow);

    console.log(response.payload);
    response.payload.forEach( function (item){
        //var object = $.parseJSON(item);
        var row = $("<tr></tr>");
        row.append($("<td></td>").text(item.name));
        row.append($("<td></td>").text(item.time));
        var dateTime = item.date.split("");
        //var time = TODO join time (last 6)
        //var datum = TODO join date (first 8)
        $("#table").append(row);
    })
}

function calculateDailyDiffer()
{

}

function calculateDailyDiffer()
{

}


