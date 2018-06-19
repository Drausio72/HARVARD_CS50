/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// new array to store placemarks and markers
var STAFF = new Array();

// bus driver's points for drop offs
var points = 0;

// People on the bus
var peopleOnBus = new Array();

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// seats taken counter
var seatsTaken = 0;

// detects if passenger has just boarded
var passengerJustOnBoard = 0;

// detects if passsenger has left bus
var passengerJustLeft = 0;

// place to teleport
var teleport = "";

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });
    
    // listen for change on Teleport Menu
    $("#dropdown").change(function() {
        $( "select option:selected" ).each(function() {
            var house = HOUSES[$(this).text()];
            shuttle.position.latitude = house.lat;
            shuttle.position.longitude = house.lng;
            shuttle.localAnchorCartesian = 
        V3.latLonAltToCartesian([house.lat, house.lng, HEIGHT]);
            viewchange();
        });   
    });
        
    // listen for change on Speed Menu
    $("#speed").change(function() {
        $( "select option:selected" ).each(function() {
            var speed = $(this).text();
            shuttle.velocity = speed;
        });   
    });

    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
function chart()
{
    var html = "<ol start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li>Empty Seat</li>";
        }
        else
        {
            var s = shuttle.seats[i];
            
            if (s.indexOf("Adams House") !== -1)
            {
                html += "<li class='adams'>" + shuttle.seats[i] + "</li>";
            }
                
            else if (s.indexOf("Cabot House") !== -1)
            {
                html += "<li class='cabot'>" + shuttle.seats[i] + "</li>";
            } 
                
            else if (s.indexOf("Currier House") !== -1)
            {
                html += "<li class='currier'>" + shuttle.seats[i] + "</li>";
            }
                
            else if (s.indexOf("Dunster House") !== -1)
            {
                html += "<li class='dunster'>" + shuttle.seats[i] + "</li>";
            }
                
            else if (s.indexOf("Eliot House") !== -1)
            {
                html += "<li class='eliot'>" + shuttle.seats[i] + "</li>";
            }
            
            else if (s.indexOf("Kirkland House") !== -1)
            {
                html += "<li class='kirkland'>" + shuttle.seats[i] + "</li>";
            }
            
            else if (s.indexOf("Leverett House") !== -1)
            {
                html += "<li class='leverett'>" + shuttle.seats[i] + "</li>";
            }
                
            else if (s.indexOf("Lowell House") !== -1)
            {
                html += "<li class='lowell'>" + shuttle.seats[i] + "</li>";
            }

                
            else if (s.indexOf("Mather House") !== -1)
            {
                html += "<li class='leverett'>" + shuttle.seats[i] + "</li>";
            }
            
            else if (s.indexOf("Pforzheimer House") !== -1)
            {
                html += "<li class='pforzheimer'>" + shuttle.seats[i] + "</li>";
            }
                
            else if (s.indexOf("Quincy House") !== -1)
            {
                html += "<li class='quincy'>" + shuttle.seats[i] + "</li>";
            }
                
            else if (s.indexOf("Winthrop House") !== -1)
            {
                html += "<li class='winthrop'>" + shuttle.seats[i] + "</li>";
            }
            
            else
            {
                html += "<li>" + shuttle.seats[i] + "</li>";
            }
            
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    passengerJustLeft = 0;
    
    for (var i = 0; i < peopleOnBus.length; i++)
    {
    
    var person = peopleOnBus[i];
    var housename = person['house'];
    var house = HOUSES[housename];     
    var d = shuttle.distance(house.lat, house.lng);
    
        
        if (d < 30 && shuttle.seats[i] != null)
        {
            points++;
            document.getElementById("announcements").innerHTML= "You just dropped " + person['name'] + ".";
            if (points == 1)
            {
                alert("Congrats, you now have " + points + " point!");
            }
            else if (points > 1)
            {
                alert("Congrats, you now have " + points + " points!");
            }
            shuttle.seats[person['seat']] = null;
            seatsTaken--;
            passengerJustLeft = 1;
            chart();
        }
        else if (d > 30 && passengerJustLeft != 1)
        {
            document.getElementById("announcements").innerHTML= "No passenger belongs to this building.";
        }

       
    }
}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
        shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
  
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup()
{   
    passengerJustOnBoard = 0;
    if (seatsTaken >= SEATS)
    {
        document.getElementById("announcements").innerHTML= "The bus is now full. Please drop off a student before getting another on board.";
        return false;
    }
    
    
    
    for (var i = 0; i < STAFF.length; i++)
    {
        var passenger = STAFF[i];
        var d = shuttle.distance(passenger.lat, passenger.lng);
        
        if (passenger.house.indexOf("Hall") !== -1 && d<=15)
        {
            document.getElementById("announcements").innerHTML= "Sorry, no freshmen allowed.";
            break;
        }
        
        if (d <= 15 && seatsTaken < SEATS && passenger.house.indexOf("Hall") === -1)
        {
            var features = earth.getFeatures();
            features.removeChild(passenger.placemark);
            passenger.marker.setMap(null);
            
            var j = 0;

            while (j < shuttle.seats.length)
            {   

                if (shuttle.seats[j] == passenger.name + " to " + passenger.house + ".")
                {
                    break;
                }
                else if (shuttle.seats[j] == null)
                {
                    shuttle.seats[j] = passenger.name + " to " + passenger.house + ".";
                    var personOnBus = {};
                    personOnBus['seat'] = j;
                    personOnBus['name'] = passenger.name;
                    personOnBus['house'] = passenger.house;
                    peopleOnBus[j] = personOnBus;
                    document.getElementById("announcements").innerHTML= "You just picked up " + passenger.name + ".";
                    chart();
                    passengerJustOnBoard = 1
                    seatsTaken++;
                    break;                       
                }
            j++;
            }
          }

          
          if (d > 15 && passengerJustOnBoard != 1)
          {
             document.getElementById("announcements").innerHTML= "There are no students in the range of 15 meters.";
          }
            
    }
}

/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });

        //remember passenger's placemark and marker for pick-up's sake
        STAFF[i] = PASSENGERS[i];
        STAFF[i].lat = building.lat;
        STAFF[i].lng = building.lng;
        STAFF[i].placemark = placemark;
        STAFF[i].marker = marker;
        
    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}
