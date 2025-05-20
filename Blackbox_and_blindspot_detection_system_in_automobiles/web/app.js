var firebaseConfig = {
  apiKey: "AIzaSyB83M6Vk2ZFoS9cqRYF6iA9Lop4eTZ-BNE",
  authDomain: "data-blackbox.firebaseapp.com",
  databaseURL: "https://data-blackbox-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "data-blackbox",
  storageBucket: "data-blackbox.appspot.com",
  messagingSenderId: "602581936920",
  appId: "1:602581936920:web:c919cbdcf3ceeeb9cc0c6d"
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

// Code for the first page
var welcomePage = document.getElementById('welcome-page');
var descriptionText = document.getElementById('description-text');
var clickInstruction = document.getElementById('click-instruction');

welcomePage.addEventListener('click', function() {
  welcomePage.classList.remove('active');
  dataTableContainer.classList.add('active');
});

setTimeout(function() {
  descriptionText.style.opacity = '1';
}, 1000);

setTimeout(function() {
  clickInstruction.style.opacity = '1';
}, 2000);

// Code for the second page
var database = firebase.database();
var sensorDataRef = database.ref('/');
var table = document.getElementById('data-table');
var dataTableContainer = document.getElementById('data-table-container');

var lastLocation = null; // Variable to store the last known location
var timestamps = {}; // Object to store timestamps for each data entry

// Function to update the table
function updateTable() {
  sensorDataRef.on('value', function(snapshot) {
      var data = snapshot.val();
      while (table.rows.length > 1) {
          table.deleteRow(1);
      }
      for (var key in data) {
          if (data.hasOwnProperty(key)) {
              var val = data[key];
              var row = table.insertRow(-1);
              var cells = [
                  row.insertCell(0),
                  row.insertCell(1),
                  row.insertCell(2),
                  row.insertCell(3),
                  row.insertCell(4),
                  row.insertCell(5)
              ];
              // Use the stored timestamp if it exists, otherwise generate a new timestamp and store it
              var timestamp = timestamps[key] ? timestamps[key] : new Date().toLocaleString();
              timestamps[key] = timestamp;
              cells[0].innerHTML = timestamp;
              var location = val.loc || lastLocation; // Use the last known location if current location is not available
              cells[1].innerHTML = '<a href="https://www.google.com/maps/search/?api=1&query=' + location + '" target="_blank">' + location + '</a>';
              cells[2].innerHTML = $('#temp-toggle').is(':checked') ? (val.T * 9/5 + 32).toFixed(2) + ' °F' : val.T.toFixed(2) + ' °C'; // Convert temperature based on the selected unit
              cells[3].innerHTML = val.H.toFixed(2) + ' %';
              cells[4].innerHTML = $('#speed-toggle').is(':checked') ? val.s.toFixed(2) + ' km/h' : (val.s * 1000 / 3600).toFixed(2) + ' m/s'; // Convert speed based on the selected unit
              var warnings = [];
              if (val.ai == 1) warnings.push('Alcohol Warning');
              if (val.wi == 1) warnings.push('Temperature Warning');
              if (val.ti == 1) warnings.push('Tilt Warning');
              if (val.vi == 1) warnings.push('Crash Warning');
              if (val.s > 80) warnings.push('Overspeed'); // Add overspeed warning if speed is more than 80 kmph
              cells[5].innerHTML = warnings.length > 0 ? warnings.join('<br>') : 'Normal'; // If no warnings, display 'Normal'
              if (warnings.length > 0) {
                  cells[5].classList.add('warning-cell');
              } else {
                  cells[5].classList.remove('warning-cell');
              }
              
              if (val.loc) {
                  lastLocation = val.loc; // Update the last known location
              }
          }
      }
  });
}

// Call the updateTable function initially and whenever a checkbox is clicked
updateTable();
$('#temp-toggle, #speed-toggle').change(updateTable);

var scrollBtn = document.getElementById("scrollBtn");
window.onscroll = function() {
  if (document.body.scrollTop > 20 || document.documentElement.scrollTop > 20) {
      scrollBtn.style.display = "block";
  } else {
      scrollBtn.style.display = "none";
  }
}

function topFunction() {
  document.body.scrollTop = 0;
  document.documentElement.scrollTop = 0;
}
