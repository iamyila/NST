autowatch = 1;
inlets = 1;
outlets = 0;

mgraphics.init();
mgraphics.relative_coords = 0;
mgraphics.autofill = 0;

var active = 1;
var playhead = 0.0;
var envelope = [];
var line = [0.95, 0.85, 0.25, 1.0];

function setActive(v) {
    active = (v !== 0) ? 1 : 0;
    mgraphics.redraw();
}

function linecolor(r, g, b, a) {
    // Accept both 0..1 and 0..255 inputs.
    if (r > 1 || g > 1 || b > 1 || a > 1) {
        line = [r / 255.0, g / 255.0, b / 255.0, a / 255.0];
    } else {
        line = [r, g, b, a];
    }
    mgraphics.redraw();
}

function setEnvelopeData() {
    envelope = arrayfromargs(arguments);
    mgraphics.redraw();
}

function drawPlayhead(v) {
    playhead = Math.max(0.0, Math.min(1.0, v));
    mgraphics.redraw();
}

function paint() {
    var w = box.rect[2] - box.rect[0];
    var h = box.rect[3] - box.rect[1];
    var alpha = active ? 1.0 : 0.35;

    // Background
    mgraphics.set_source_rgba(0.08, 0.08, 0.08, 0.35);
    mgraphics.rectangle(0, 0, w, h);
    mgraphics.fill();

    // Envelope polyline (expects x/y pairs in 0..1 range)
    if (envelope.length >= 4 && (envelope.length % 2) === 0) {
        mgraphics.set_line_width(1.5);
        mgraphics.set_source_rgba(line[0], line[1], line[2], line[3] * alpha);
        for (var i = 0; i < envelope.length; i += 2) {
            var x = Math.max(0.0, Math.min(1.0, envelope[i])) * w;
            var y = (1.0 - Math.max(0.0, Math.min(1.0, envelope[i + 1]))) * h;
            if (i === 0) {
                mgraphics.move_to(x, y);
            } else {
                mgraphics.line_to(x, y);
            }
        }
        mgraphics.stroke();
    }

    // Playhead
    var px = playhead * w;
    mgraphics.set_line_width(1.0);
    mgraphics.set_source_rgba(1.0, 1.0, 1.0, 0.8 * alpha);
    mgraphics.move_to(px, 0);
    mgraphics.line_to(px, h);
    mgraphics.stroke();
}
