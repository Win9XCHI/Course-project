var map;

function initialize() {
    var mapOptions = {
        zoom: 6,
        center: new google.maps.LatLng(48.45, 35.02)
    };

    map = new google.maps.Map(document.getElementById("map"), mapOptions);
}


google.maps.event.addDomListener(window, "load", initialize);


function SetMarker(location, title) {
    var marker = new google.maps.Marker({
        position: location, //new google.maps.LatLng(locations[i][1], locations[i][2]),
        map: map,
        title: title
    });
}

function SetLine(flightPlanCoordinates) {
    var flightPath = new google.maps.Polyline({
        path: flightPlanCoordinates,
        geodesic: true,
        strokeColor: '#FF0000',
        strokeOpacity: 1.0,
        strokeWeight: 2
      });
    flightPath.setMap(map);
}

function ClearMarkerAndLine() {
    marker.setMap(null);
    flightPath.setMap(null);
}
  

/*var $date_field = $('dat');
	$date_field.minical({
		date_format: function(date) {
		  return [date.getDate(), date.getMonth() + 1, date.getFullYear()].join("-");
		}
	})*/
/**
 * First example. Using "setTimeout" function.
 *-/
var location1 = new google.maps.LatLng(48.5, 35.2);
var title1 = "Dnipropetrovsk";

// Will NOT work because google map has not load yet.
SetMarker();

// Will work after 3 seconds delay.
setTimeout(SetMarker, 3000, location1, title1);


/**
 * Second example. Using click event of DIV element.
 marker.setMap(null);
 flightPath.setMap(null);
 */

/*
var locations = [
    ["Название метки 1", 50.4094919,30.6038815],
    ["Название метки 2", 50.427342,30.469137],
];

var elementToClick = document.getElementById("click_to_view_a_marker");
for (i = 0; i < locations.length; i++) {
    elementToClick.onclick = function() {
        SetMarker(locations[i][1], locations[i][2]);
    };
}
*/
var location1 = { lat: 48.4758334, lng: 35.0110233 };
var title1 = "Dnipro";
var location2 = { lat: 50.43, lng: 30.52 };
var title2 = "Kyiv";

var flightPlanCoordinates = [location1,
                            { lat: 48.5294442, lng: 34.5614104 },
                            { lat: 48.483099, lng: 34.2331185 },
                            { lat: 48.4150011, lng: 33.6943868 },
                            { lat: 48.6699402, lng: 33.1362609 },
                            { lat: 48.709917, lng: 32.6764314 },
                            { lat: 49.2062982, lng: 31.8852692 },
                            location2];

var elementToClick = document.getElementById("click_to_view_a_marker");
elementToClick.onclick = function() {
    SetMarker(location1, title1);
    SetMarker(location2, title2);
    SetLine(flightPlanCoordinates);
};

