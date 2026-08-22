// OpenSlip phone UI (served from the device, no CDN)
// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <Arduino.h>

static const char PAGE_INDEX[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>OpenSlip</title>
<style>
:root{--bg:#101418;--card:#1a222b;--ink:#e8eef4;--muted:#8fa3b5;--acc:#e6b325;--ok:#3dcc8a;--bad:#e05757;--line:#2b3845}
*{box-sizing:border-box}
body{margin:0;font-family:Segoe UI,Roboto,sans-serif;background:var(--bg);color:var(--ink)}
header{padding:14px 16px;border-bottom:1px solid var(--line);display:flex;justify-content:space-between;align-items:center;gap:8px}
h1{font-size:16px;margin:0}
.ver{background:#e6b325;color:#1a1400;border-radius:999px;padding:4px 10px;font-weight:700;font-size:13px}
.wrap{padding:12px;max-width:720px;margin:0 auto}
.card{background:var(--card);border:1px solid var(--line);border-radius:12px;padding:14px;margin:0 0 12px}
.si{font-size:64px;line-height:1;font-variant-numeric:tabular-nums;color:var(--acc);text-align:center}
.sub{text-align:center;color:var(--muted);margin-top:6px}
.row{display:flex;gap:8px;flex-wrap:wrap;margin-top:10px}
button,input,select,a.btn{appearance:none;border:0;border-radius:10px;padding:12px 14px;font-size:16px;background:#2a3642;color:var(--ink);text-decoration:none;display:inline-block}
button.pri{background:var(--acc);color:#1a1400;font-weight:700}
button.ok{background:var(--ok);color:#062015;font-weight:700}
button.bad{background:var(--bad);color:#fff;font-weight:700}
button:disabled{opacity:.45}
input,select{flex:1;min-width:90px;background:#0f151b;border:1px solid var(--line)}
label{display:block;color:var(--muted);font-size:12px;margin:8px 0 4px}
.grid{display:grid;grid-template-columns:1fr 1fr;gap:8px}
.kv{display:flex;justify-content:space-between;border-bottom:1px solid var(--line);padding:6px 0;font-size:14px}
.small{font-size:13px;color:var(--muted)}
.msg{background:#2a2210;border:1px solid #5a4a20;color:#f0d58a;border-radius:10px;padding:10px;margin:0 0 12px;display:none}
.pills{display:flex;gap:6px;flex-wrap:wrap}
.pill{font-size:12px;border-radius:999px;padding:6px 10px;background:#2a3642}
.pill.on{background:#163628;color:var(--ok)}
.pill.off{background:#3a1c1c;color:#ffb3b3}
table{width:100%;border-collapse:collapse;font-size:13px}
th,td{text-align:left;padding:6px 4px;border-bottom:1px solid var(--line)}
</style>
</head>
<body>
<header>
  <h1>OpenSlip</h1>
  <span class="ver" id="ver">…</span>
</header>
<div class="wrap">
  <div class="msg" id="msg"></div>
  <div class="card">
    <div class="pills">
      <span class="pill" id="pTmc">TMC</span>
      <span class="pill" id="pEnc">Encoder</span>
      <span class="pill" id="pOled">OLED</span>
      <span class="pill" id="pArm">Motor</span>
      <span class="pill" id="pAp">AP</span>
    </div>
    <div class="si" id="si">—.——</div>
    <div class="sub" id="ang">mast —.—° from vertical</div>
    <div class="row">
      <button class="ok" onclick="api('/api/arm?on=1','POST')">Enable motor</button>
      <button onclick="api('/api/arm?on=0','POST')">Disable</button>
      <a class="btn pri" href="/update">OTA update</a>
    </div>
    <div class="row">
      <button onclick="step(-0.05)">−0.05</button>
      <button onclick="step(-0.01)">−0.01</button>
      <button class="pri" onclick="step(0.01)">+0.01</button>
      <button class="pri" onclick="step(0.05)">+0.05</button>
    </div>
    <div class="row">
      <input id="goto" type="number" step="0.01" min="0" max="1.2" value="0.30">
      <button class="pri" onclick="go()">Go to SI</button>
      <button onclick="api('/api/stop','POST')">Stop</button>
    </div>
    <div class="row">
      <button onclick="api('/api/jog?dir=-1','POST')">Jog −</button>
      <button onclick="api('/api/jog?dir=1','POST')">Jog +</button>
      <button onclick="api('/api/zero','POST')">Set vertical zero</button>
    </div>
    <p class="small" id="hint">Motor stays disabled until you enable it. Safe with no motor attached.</p>
  </div>

  <div class="card">
    <div class="small">Protocol: start more vertical, increase SI until slip, record to 0.01</div>
    <div class="row">
      <select id="dir"><option>N</option><option>E</option><option>S</option><option>W</option></select>
      <button class="ok" onclick="rec('hold')">No slip</button>
      <button class="bad" onclick="rec('slip')">Slip</button>
      <a class="btn" href="/api/readings.csv">CSV</a>
      <button onclick="api('/api/clear','POST')">Clear</button>
    </div>
    <table>
      <thead><tr><th>#</th><th>Dir</th><th>SI</th><th>Deg</th><th>Result</th></tr></thead>
      <tbody id="tb"></tbody>
    </table>
  </div>

  <div class="card">
    <div class="kv"><span>Encoder counts</span><b id="enc">—</b></div>
    <div class="kv"><span>Motor</span><b id="mot">—</b></div>
    <div class="kv"><span>TMC2209</span><b id="tmc">—</b></div>
    <div class="kv"><span>OLED</span><b id="oled">—</b></div>
    <div class="kv"><span>Wi-Fi STA</span><b id="wf">—</b></div>
    <div class="kv"><span>Build</span><b id="bld">—</b></div>
    <div class="row">
      <button class="pri" onclick="api('/api/oledtest','POST')">Flash OLED white 15s</button>
    </div>
  </div>

  <div class="card">
    <b>Calibration</b>
    <label>Known slip index at current mast</label>
    <div class="row">
      <input id="knownsi" type="number" step="0.01" value="0.50">
      <button onclick="api('/api/cal_si?si='+knownsi.value,'POST')">Calibrate from SI</button>
    </div>
    <div class="row">
      <input id="knowndeg" type="number" step="0.1" value="26.57">
      <button onclick="api('/api/cal_deg?deg='+knowndeg.value,'POST')">Calibrate from degrees</button>
    </div>
    <label>Gear ratio (mast deg / motor deg). Direct drive = 1</label>
    <div class="row">
      <input id="gear" type="number" step="0.001" value="1">
      <button onclick="saveCfg()">Save settings</button>
    </div>
    <div class="grid">
      <div><label>Invert direction</label><select id="inv"><option value="0">No</option><option value="1">Yes</option></select></div>
      <div><label>RMS current mA</label><input id="rms" type="number" value="800"></div>
    </div>
  </div>

  <div class="card">
    <b>Home Wi-Fi (optional, keeps AP on)</b>
    <label>SSID</label><input id="ssid">
    <label>Password</label><input id="pass" type="password">
    <div class="row">
      <button class="pri" onclick="saveWifi()">Save and connect</button>
    </div>
    <p class="small">AP OpenSlip stays up so the phone UI and OTA still work in the field.</p>
  </div>
</div>
<script>
async function api(url, method='GET'){
  const r = await fetch(url,{method});
  return r.json().catch(()=>({}));
}
function step(d){ api('/api/nudge?dsi='+d,'POST'); }
function go(){ api('/api/goto?si='+document.getElementById('goto').value,'POST'); }
function rec(kind){
  const dir=document.getElementById('dir').value;
  api('/api/record?result='+kind+'&dir='+dir,'POST').then(renderReadings);
}
function saveCfg(){
  const q = new URLSearchParams({gear:gear.value, invert:inv.value, rms:rms.value});
  api('/api/config?'+q.toString(),'POST');
}
function saveWifi(){
  const q = new URLSearchParams({ssid:ssid.value, pass:pass.value});
  api('/api/wifi?'+q.toString(),'POST');
}
function pill(el, on, onTxt, offTxt){
  el.className = 'pill ' + (on?'on':'off');
  el.textContent = on?onTxt:offTxt;
}
function renderReadings(j){
  if(!j || !j.readings) return;
  tb.innerHTML = j.readings.map((x,i)=>`<tr><td>${i+1}</td><td>${x.dir}</td><td>${x.si.toFixed(2)}</td><td>${x.deg.toFixed(2)}</td><td>${x.result}</td></tr>`).join('');
}
async function tick(){
  const j = await api('/api/status');
  ver.textContent = 'v'+(j.version||'?');
  si.textContent = (j.si??0).toFixed(2);
  ang.textContent = 'mast '+(j.deg??0).toFixed(2)+'° from vertical';
  enc.textContent = j.enc;
  mot.textContent = j.armed ? (j.moving ? 'moving to '+(j.target??0).toFixed(2) : 'holding') : 'disabled';
  tmc.textContent = j.tmc || 'not found';
  oled.textContent = j.oledInfo || '—';
  wf.textContent = j.ip||'not joined';
  bld.textContent = j.build||'';
  pill(pTmc, !!j.tmcOk, 'TMC ok', 'TMC not found');
  pill(pEnc, !!j.encLive, 'Encoder live', 'No encoder yet');
  pill(pOled, !!j.oledOk, 'OLED on', 'OLED off');
  pill(pArm, !!j.armed, 'Motor enabled', 'Motor disabled');
  pill(pAp, true, 'AP '+(j.ap||''), 'AP');
  if(j.msg){ msg.style.display='block'; msg.textContent=j.msg; } else { msg.style.display='none'; }
  if(j.gear!=null) gear.value=j.gear;
  if(j.invert!=null) inv.value=j.invert?'1':'0';
  if(j.rms!=null) rms.value=j.rms;
  renderReadings(j);
}
setInterval(tick, 400);
tick();
</script>
</body>
</html>
)HTML";

static const char PAGE_UPDATE[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html><head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>OTA</title>
<style>
body{font-family:sans-serif;background:#101418;color:#e8eef4;max-width:480px;margin:40px auto;padding:16px}
input,button{font-size:16px;padding:12px;border-radius:8px;border:0;margin:6px 0}
button{background:#e6b325;color:#1a1400;font-weight:700;width:100%}
.box{background:#1a222b;padding:16px;border-radius:12px}
.small{color:#8fa3b5}
</style>
</head><body>
<div class="box">
<h2>Firmware OTA</h2>
<p>Current: <b id="v">…</b></p>
<p class="small">Choose the .bin (application image, not a merged flash dump). Password openslip. Keep the phone on OpenSlip Wi-Fi. After OK, wait 10s and reopen the app — version should change.</p>
<form method="POST" action="/update?pass=openslip" enctype="multipart/form-data" onsubmit="s.textContent='Uploading… keep this page open';">
<input type="file" name="firmware" accept=".bin" required>
<button type="submit">Update and reboot</button>
</form>
<p id="s" class="small"></p>
<p><a href="/" style="color:#e6b325">Back</a></p>
</div>
<script>
fetch('/api/status').then(r=>r.json()).then(j=>{v.textContent='v'+(j.version||'?')+'  '+ (j.build||'');});
</script>
</body></html>
)HTML";
