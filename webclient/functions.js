function httpGetAsync(theUrl, callback)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200) {
            $("#info_text").text("Erfolgreich aktualisiert!");
            $("#info_text").addClass("success");
            callback(xmlHttp.responseText);
        } else if (xmlHttp.status == 500) {
            $("#info_text").text("Fehler! Die gesuchten Messresultate konnten nicht gefunden werden.");
            var nameval = $("#name").val() === "" ? "*" : $("#name").val();
            var dateval = $("#date").val() === "" ? "*" : $("#date").val();
            $("#info_text_detail").text(nameval + " oder " + dateval);
            $("#info_text").addClass("fail");
            $("#info_text_detail").addClass("fail");
        } else if (xmlHttp.status == 501) {
            $("#info_text").text("Fehler! Falsche Funktionalität abgerufen.");
            $("#info_text").addClass("fail");
        }
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
        var time = item.date.slice(8,14);
        time = time.slice(0,2) + ":" + time.slice(2,4) + ":" + time.slice(4,6);
        var datum = item.date.slice(0,8);
        datum = datum.slice(0,4) + "-" + datum.slice(4,6) + "-" + datum.slice(6,8);
        row.append($("<td></td>").text(datum));
        row.append($("<td></td>").text(time));

        $("#table").append(row);
    })
}

function calculateDailyDiffer()
{
    
}

function calculateMeasureDiffer()
{

}

function refreshInput(clockname, date) 
{
    $("#info_text").text("verarbeiten....");
    $("#info_text").removeClass("fail");
    $("#info_text").removeClass("success");
    $("#info_text").addClass("info");
    $("#info_text_detail").empty();

    if ( date != "" ){
        date = date.split("/");
        var day = date[1];
        var month = date[0];
        var year = date[2];
        date = year + month + day;
    } 
    date += "%";

    if ( clockname === "" )
        clockname = "%";
    var url = "http://localhost:8080?name=" + clockname + "&date=" + date;
    console.log(url);
    httpGetAsync(url, displayResponse);
}
