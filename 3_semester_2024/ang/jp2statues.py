# Statues of John Paul II in Poland

import requests
import json

# Define Overpass API endpoint
overpass_url = "http://overpass-api.de/api/interpreter"

# Define the bounding box for Poland (approximate coordinates)
# Bounding box: [south, west, north, east]
bbox = [48.00, 13.00, 55.00, 25.00]  # Approx. coordinates covering Poland

# Define the Overpass QL query using the bounding box
overpass_query = f"""
[out:json];
(
  node["name"~"Jan Paweł II|Jana Pawła II"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
  node["name"~"Jan Paweł II|Jana Pawła II"]["historic"="memorial"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
  node["name"~"Jan Paweł II|Jana Pawła II"]["historic"="monument"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
  node["name"~"Jan Paweł II|Jana Pawła II|JP II|JPII"]["memorial"="statue"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
  node["name"~"Jan Paweł II|Jana Pawła II|JP II|JPII"]["artwork_type"="statue"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
  node["name"~"Jan Paweł II|Jana Pawła II|JP II|JPII"]["amenity"="statue"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
  node["subject"~"Jan Paweł II|Jana Pawła II|JP II|JPII"]["memorial"="statue"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
  node["subject"~"Jan Paweł II|Jana Pawła II|JP II|JPII"]["artwork_type"="statue"]({bbox[0]},{bbox[1]},{bbox[2]},{bbox[3]});
);
out body;
>;
out skel qt;
"""

# Send the request
response = requests.get(overpass_url, params={'data': overpass_query})
data = response.json()

print("BEGIN_RAW_DATA")
print(data)
print("END_RAW_DATA")

# Parse and display the results
statues = []
for element in data['elements']:
    if 'tags' in element and 'name' in element['tags']:
        statue_info = {
            'name': element['tags'].get('name'),
            'lat': element.get('lat'),
            'lon': element.get('lon'),
            'id': element.get('id'),
            'height': element['tags'].get('height'),
            'wikidata': element['tags'].get('wikidata'),
            'wikipedia': element['tags'].get('wikipedia'),
            'tourism': element['tags'].get('tourism'),
            'subject:wikidata': element['tags'].get('subject:wikidata')
        }
        statues.append(statue_info)

# Display results
print(f"Found {len(statues)} statues of John Paul II in Poland (Bounding Box).")
for statue in statues:
    print(statue)
