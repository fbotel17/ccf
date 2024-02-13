/* API Mapbox key */
mapboxgl.accessToken = 'pk.eyJ1IjoiMHZlcmRyYXciLCJhIjoiY2t1ZHFna2k4MWQ1YzMybDlzOWMxbnI2ZyJ9.UBRgQa9a0LYDml-i4GjR0Q';

const map = new mapboxgl.Map({
    container: 'map',
    style: 'mapbox://styles/mapbox/streets-v11',
    center: [2.2997429, 49.8775471], // Init the position of the center in the map
    zoom: 1
});

function point(message)
{
    const point = {
        'type': 'geojson',
        'data': {
            'type': 'Feature',
            'properties': {},
            'geometry': {
                'type': 'LineString',
                'coordinates': []
            }
        }
    };

    marker(message[0], map, point);

}

function marker(data, map, point){
    var id          = data[0];
    var latitude    = data[1];
    var longitude   = data[2];
    var date        = data[3];

    // Creation of the marker
    var el = document.createElement('div');
    el.className = 'marker';
    el.style.backgroundColor = '#ff0000';
    el.style.border = 'solid black 1px';
    el.style.borderRadius = '10px'
    el.style.width = '15px';
    el.style.height = '15px';
    el.style.backgroundSize = '100%';

    const popup = new mapboxgl.Popup({ offset: 25 }).setHTML(
        '<h3>['+latitude+', '+longitude+']</h3><p>ID : '+id+'</p><p>Date: '+date+'</p>'
    );
    // Add the marker on the map
    new mapboxgl.Marker(el).setLngLat([latitude, longitude]).setPopup(popup).addTo(map);

    point.data.geometry.coordinates.push([latitude, longitude]);
}