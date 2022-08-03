async function fetch_angles() {
  res = await fetch('tilt');
  text = await res.text();
  res_obj = JSON.parse(text);

  x = res_obj['x'];
  y = res_obj['y'];

  tilt_x_input = document.getElementById('tilt-x-input');
  tilt_y_input = document.getElementById('tilt-y-input');
  tilt_x_input.value = x;
  tilt_y_input.value = y;
}

async function tilt(axis) {
  tilt_input = document.getElementById(`tilt-${axis}-input`);
  val = tilt_input.value;
  val = +val ? +val : 0;

  await fetch(`tilt/${axis}`, {
    method: 'POST',
    headers: {
      Accept: 'application/json',
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ value: val }),
  });
}

fetch_angles();
