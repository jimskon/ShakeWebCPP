// JavaScript for Shakespeare lookup
// Jim Skon, Kenyon College, 2021
var searchType;  // Save search type here

// search prarents for a matching selector
var getClosest = function (elem, selector) {
	for ( ; elem && elem !== document; elem = elem.parentNode ) {
		if ( elem.matches( selector ) ) return elem;
	}
	return null;
};

console.log("Start!");
// Add a click event for the search button
document.querySelector("#search-btn").addEventListener("click", (e) => {
    getMatches();
});

function processResults(results) {
    console.log("Results:",results);
    document.querySelector('#searchresults').innerHTML = results;
}

function clearResults() {
    document.querySelector('#searchresults').innerHTML = "";
}

function getMatches(){
    console.log("getMatches!");
    var searchStr=document.querySelector('#search').value;

    // Ignore short requests
    if (searchStr.length < 2) return;

    // Clear the previous results
    document.querySelector('#searchresults').innerHTML = "";

    fetch('/cgi-bin/shakewebcpp.cgi?word='+searchStr, {
	method: 'get'
    })
	.then (response => response.text() )
        .then (data => processResults(data))
	.catch(error => {
	    {alert("Error: Something went wrong:"+error);}
	})
}


