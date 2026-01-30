/*-----------------------------------------*\
|	jsui adsr                               |
|   Live-like asdr envelope                 |
|											|
|	by Nico Starke							|
|	nico.starke@ableton.com					|
|											|
|	September 2017							|
\*-----------------------------------------*/

outlets = 2;


// mgraphics initialization
mgraphics.init();					// initialize mgraphics
mgraphics.relative_coords = 0;		// coordinate system: x, y, width height
mgraphics.autofill = 0;				// we want to fill the paths ourself


// global variables

var linecolor = [1., 0.71, 0.2, 1.];
declareattribute("linecolor", "getlinecolor", "setlinecolor", 1);

var inactivecolor = [0.5, 0.5, 0.5, 1.];
declareattribute("inactivecolor", "getinactivecolor", "setinactivecolor", 1);

var linestrength = 1.5;
var breakpointsize = 5;
var margin = breakpointsize/2;
var breakpointoutline = 1;
var highlightcolor = [1., 1., 1., 1.];
var playheadcolor = [1., 1., 1., 1.];
var showzigzag = 0; // only for debugging
var playhead = [-5, -5];
var isPlaying = 0;
var isEnabled = 1;


var boxwidth = this.box.getattr("presentation_rect")[2];
var boxheight = this.box.getattr("presentation_rect")[3];
var scalefactorX = boxwidth / (boxwidth + 4 * margin); 
var scalefactorY = boxheight/ (boxheight + 4 * margin);
var width = boxwidth * scalefactorX;
var height = boxheight * scalefactorY;
var sustainleftbound = width / 3;
var sustainrightbound = width / 3 * 2;

var env = { attack: 0, 
            aslope: 0.5, 
            decay: 39, 
            dslope: 0.5,
            sustain: 22,
            release: 140,
            rslope: 0.5};

var hover = {   attack: 0,
                decay: 0,
                release: 0
            };


var zigzagcoords = []; // holds coords of the interpolation fragments
createFragments();

	
function paint(){
	mgraphics.set_line_cap("round");
	mgraphics.set_line_join("round");
	
	with (mgraphics) {	

        var drawcolor = (isEnabled) ? linecolor : inactivecolor;
		set_source_rgba(drawcolor);
		set_line_width(linestrength);

		// draw attack segment
        var p1 = 0; 
        p1 = gethandles([margin, height+margin], [env.attack+margin, margin], env.aslope);
        move_to(margin, height+margin); 
		curve_to(p1[0], p1[1], p1[0], p1[1], env.attack+margin, margin);

		// draw decay segment
        p1 = gethandles([env.attack+margin, margin], [env.decay+margin, env.sustain+margin], env.dslope);
		curve_to(p1[0], p1[1], p1[0], p1[1], env.decay+margin, env.sustain+margin);

        // draw sustain segment
        line_to(sustainrightbound+margin, env.sustain+margin);

        // draw release segment
        p1 = gethandles([sustainrightbound+margin, env.sustain+margin], [env.release+margin, height+margin], env.rslope);
		curve_to(p1[0], p1[1], p1[0], p1[1], env.release+margin, height+margin);

		stroke();
        
        // draw handles
		set_line_width(breakpointoutline);

        var highlightdrawcolor = (isEnabled) ? highlightcolor : inactivecolor;

        if (hover.attack == 0) set_source_rgba(drawcolor);
        else set_source_rgba(highlightdrawcolor);
	    rectangle(env.attack, 0, breakpointsize, breakpointsize);
		stroke();

        if (hover.decay == 0) set_source_rgba(drawcolor);
        else set_source_rgba(highlightdrawcolor);
	    rectangle(env.decay, env.sustain, breakpointsize, breakpointsize);
        stroke();

        if (hover.release == 0) set_source_rgba(drawcolor);
        else set_source_rgba(highlightdrawcolor);
	    rectangle(env.release, height, breakpointsize, breakpointsize);
		stroke();

	    // draw playhead
		set_source_rgba(playheadcolor);
        if (isPlaying){
		ellipse(playhead[0]-breakpointsize/2, playhead[1]-breakpointsize/2, breakpointsize, breakpointsize);
		fill();
        }

		if (showzigzag){
		    for(a=0; a < zigzagcoords.length; a++){
				ellipse(zigzagcoords[a][0]-1, zigzagcoords[a][1]-1, 2, 2);
				set_source_rgba([1, 1, 1, 0.6]);
				stroke();
			}
	    }
					
	}
}


// calculate bezier points
function gethandles(startpoint, endpoint, curve){
	var	p1x = (endpoint[0] - startpoint[0]) * curve + startpoint[0];
	var	p1y = (endpoint[1] - startpoint[1]) * (1-curve) + startpoint[1];
	return [p1x, p1y];
}


function createFragments(){
		
    var segments = [];
    segments[0] = [margin, height+margin, 0.5];
    segments[1] = [env.attack+margin, margin, env.aslope];
    segments[2] = [env.decay+margin, env.sustain+margin, env.dslope];
    segments[3] = [sustainrightbound+margin, env.sustain+margin, 0.5];
    segments[4] = [env.release+margin, height+margin, env.rslope];


    zigzagcoords = [];
    zigzagcoords[0] = [margin, height+margin];


	for (var i = 0; i < (segments.length-1); i++){

		var start = segments[i];
		var end = segments[i+1];
		var handle = gethandles(start, end, segments[i+1][2]);

		var b = interpolate([start, handle, handle, end]);

		var fragments = 6;
		var step = 1/fragments;

		
		// calculate fragments for each segment
		for (var a = 1; a <= fragments; a++){
			var t = a * step;
			var point = b(t);
			point[0] = Math.round(point[0]);
			
			// actual coords of the points
			zigzagcoords.push(point);
		}
    }
}



function drawPlayhead(x){

    if (x >= 0)
        isPlaying = 1;
    else
        isPlaying = 0;

	// get current fragment
	var source = 0;
	var dest = 0;

	for (var i = 0; i < zigzagcoords.length; i++){		
		if (x < zigzagcoords[i][0]){
            source = zigzagcoords[i-1];
            dest = zigzagcoords[i];
            break;
        }
    }
		
	if (source && dest){

	    // calculate iterpolated Y value 
		var interpolatedY = source[1] + (x - source[0]) * ((dest[1] - source[1]) / (dest[0] - source[0]))
		playhead = [x, interpolatedY];
	}

    else
		playhead = [x, -10];
    
	mgraphics.redraw();
}



function interpolate(bpcoords){

	return function (t) {	

		for (var a = bpcoords; a.length > 1; a = b)  // do..while loop in disguise
			for (var i = 0, b = [], j; i < a.length - 1; i++)  // cycle over control points
				for (b[i] = [], j = 0; j < a[i].length; j++)  // cycle over dimensions
					b[i][j] = a[i][j] * (1 - t) + a[i+1][j] * t;  // interpolation	
		return a[0];
	}
}


function onidle(x, y, button, cmd, shift, capslock, option, ctrl){
    
    if (x > env.attack-breakpointsize+margin && x < env.attack+breakpointsize+margin && y < 0 + breakpointsize+margin)
        hover.attack = 1;
    else 
        hover.attack = 0;
    
    if (x > env.decay-breakpointsize+margin && x < env.decay+breakpointsize+margin && y > env.sustain - breakpointsize + margin && y < env.sustain + breakpointsize + margin)
        hover.decay = 1;
    else 
        hover.decay = 0;

    if (x > env.release-breakpointsize+margin && x < env.release+breakpointsize+margin && y > height - breakpointsize)
        hover.release = 1;
    else 
        hover.release = 0;
	mgraphics.redraw();
} 

function onidleout(x, y){
    hover.attack = 0;
    hover.decay = 0;
    hover.release = 0;
	mgraphics.redraw();
}

function ondrag (x, y, button, cmd, shift, capslock, option, ctrl){
    
    if (hover.attack){
        var decayoffset = env.decay - env.attack;
        env.attack = clamp(x, 0, width / 3);
        env.decay = env.attack + decayoffset;
    }

    if (hover.decay){
        env.decay = clamp(x, env.attack, sustainleftbound + env.attack);
        env.sustain = clamp(y*scalefactorY, 0, height);
    }

    if (hover.release){
        env.release = clamp(x, sustainrightbound, width);

    }

    createFragments();
    drawPlayhead(playhead[0]);
	mgraphics.redraw();
    outputEnvelopeData();
} 


function clamp(num, min, max) {
	return num <= min ? min : num >= max ? max : num;
}

function setEnvelopeData(attack, aslope, decay, dslope, sustain, release, rslope){
    env.attack = (width / 3) * attack;
    env.aslope = aslope;
    env.decay = (width / 3) * decay + env.attack;
    env.dslope = dslope;
    env.sustain = (height) * (1 - sustain);
    env.release = (width / 3) * release + sustainrightbound;
    env.rslope = rslope;
    createFragments();
    drawPlayhead(playhead[0]);
    outlet(1, env.attack+margin, env.decay+margin, sustainrightbound+margin, env.release+margin);
	mgraphics.redraw();
}

function outputEnvelopeData(){

    var a = 0;
    var d = 0;
    var s = 0;
    var r = 0;

    a = env.attack / (width / 3);
    d = (env.decay / (width / 3)) - a;
    s = 1 - env.sustain / height;
    r = (env.release - sustainrightbound) / (width / 3);
    
    outlet(0, a, env.aslope, d, env.dslope, s, r, env.rslope);
    outlet(1, env.attack+margin, env.decay+margin, sustainrightbound+margin, env.release+margin);
}

function setActive(x){
    isEnabled = x;
	mgraphics.redraw();
}


// getter and setter functions for attributes in inspector

function setlinecolor(r, g, b, a) {
    linecolor = [r, g, b, a];
    mgraphics.redraw();
}

function getlinecolor() {
    return linecolor;
}

function setinactivecolor(r, g, b, a) {
    inactivecolor = [r, g, b, a];
    mgraphics.redraw();
}

function getinactivecolor() {
    return inactivecolor;
}

