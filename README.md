<!DOCTYPE html>
<html lang="en"><script>

/// begin: [code injected by Web MIDI API browser extension]
navigator.requestMIDIAccess=function(){if(typeof JZZ=='undefined')window.JZZ=(function _JZZ() {

  var _scope = typeof window === 'undefined' ? global : window;
  var _version = '1.0.2';
  var i, j, k, m, n;

  var _time = Date.now || function () { return new Date().getTime(); };
  var _startTime = _time();
  var _now = typeof performance != 'undefined' && performance.now ?
    function() { return performance.now(); } : function() { return _time() - _startTime; };
  var _schedule = function(f) {
    setTimeout(f, 0);
  };

  // _R: common root for all async objects
  function _R() {
    this._orig = this;
    this._ready = false;
    this._queue = [];
    this._log = [];
  }
  _R.prototype._exec = function() {
    while (this._ready && this._queue.length) {
      var x = this._queue.shift();
      x[0].apply(this, x[1]);
    }
  };
  _R.prototype._push = function(func, arg) { this._queue.push([func, arg]); _R.prototype._exec.apply(this); };
  _R.prototype._slip = function(func, arg) { this._queue.unshift([func, arg]); };
  _R.prototype._pause = function() { this._ready = false; };
  _R.prototype._resume = function() { this._ready = true; _R.prototype._exec.apply(this); };
  _R.prototype._break = function(err) { this._orig._bad = true; this._orig._log.push(err || 'Unknown JZZ error'); };
  _R.prototype._repair = function() { this._orig._bad = false; };
  _R.prototype._crash = function(err) { this._break(err); this._resume(); };
  _R.prototype._err = function() { return this._log[this._log.length - 1]; };
  _R.prototype.log = function() { return _clone(this._log); };
  _R.prototype._image = function() {
    var F = function() {}; F.prototype = this._orig;
    var ret = new F();
    ret._ready = false;
    ret._queue = [];
    return ret;
  };
  _R.prototype._thenable = function() {
    var self = this;
    var F = function() {}; F.prototype = self;
    var ret = new F();
    ret.then = function(good, bad) { self._push(_then, [good, bad]); return this; };      
    return ret;
  };
  function _then(good, bad) {
    if (this._bad) {
      if (bad instanceof Function) bad.apply(this, [new Error(this._err())]);
    }
    else {
      if (good instanceof Function) good.apply(this, [this]);
    }
  }
  function _wait(obj, delay) {
    if (this._bad) obj._crash(this._err());
    else setTimeout(function() { obj._resume(); }, delay);
  }
  _R.prototype.wait = function(delay) {
    if (!delay) return this;
    var ret = this._image();
    this._push(_wait, [ret, delay]);
    return ret._thenable();
  };
  function _kick(obj) { if (this._bad) obj._break(this._err()); obj._resume(); }
  function _rechain(self, obj, name) {
    self[name] = function() {
      var arg = arguments;
      var ret = obj._image();
      this._push(_kick, [ret]);
      return ret[name].apply(ret, arg);
    };
  }
  function _and(q) {
    if (!this._bad) {
      if (q instanceof Function) q.apply(this); else console.log(q);
    }
  }
  _R.prototype.and = function(func) { this._push(_and, [func]); return this._thenable(); };
  function _or(q) {
    if (this._bad) {
      if (q instanceof Function) q.apply(this); else console.log(q);
    }
  }
  _R.prototype.or = function(func) { this._push(_or, [func]); return this._thenable(); };

  _R.prototype._info = {};
  _R.prototype.info = function() {
    var info = _clone(this._orig._info);
    if (typeof info.engine == 'undefined') info.engine = 'none';
    if (typeof info.sysex == 'undefined') info.sysex = true;
    return info;
  };
  _R.prototype.name = function() { return this.info().name; };

  function _close(obj) {
    if (this._bad) obj._crash(this._err());
    else {
      this._break('Closed');
      obj._resume();
    }
  }
  _R.prototype.close = function() {
    var ret = new _R();
    if (this._close) this._push(this._close, []);
    this._push(_close, [ret]);
    return ret._thenable();
  };

  function _tryAny(arr) {
    if (!arr.length) {
      this._break();
      return;
    }
    var func = arr.shift();
    if (arr.length) {
      var self = this;
      this._slip(_or, [ function() { _tryAny.apply(self, [arr]); } ]);
    }
    try {
      this._repair();
      func.apply(this);
    }
    catch (err) {
      this._break(err.toString());
    }
  }

  function _push(arr, obj) {
    for (var i = 0; i < arr.length; i++) if (arr[i] === obj) return;
    arr.push(obj);
  }
  function _pop(arr, obj) {
    for (var i = 0; i < arr.length; i++) if (arr[i] === obj) {
      arr.splice(i, 1);
      return;
    }
  }

  // _J: JZZ object
  function _J() {
    _R.apply(this);
  }
  _J.prototype = new _R();

  function _clone(obj, key, val) {
    if (typeof key == 'undefined') return _clone(obj, [], []);
    if (obj instanceof Object) {
      for (var i = 0; i < key.length; i++) if (key[i] === obj) return val[i];
      var ret;
      if (obj instanceof Array) ret = []; else ret = {};
      key.push(obj); val.push(ret);
      for(var k in obj) if (obj.hasOwnProperty(k)) ret[k] = _clone(obj[k], key, val);
      return ret;
    }
    return obj;
  }
  _J.prototype._info = { name: 'JZZ.js', ver: _version, version: _version, inputs: [], outputs: [] };

  var _outs = [];
  var _ins = [];
  var _outsW = [];
  var _insW = [];

  function _postRefresh() {
    _jzz._info.engine = _engine._type;
    _jzz._info.version = _engine._version;
    _jzz._info.sysex = _engine._sysex;
    _jzz._info.inputs = [];
    _jzz._info.outputs = [];
    _outs = [];
    _ins = [];
    _engine._allOuts = {};
    _engine._allIns = {};
    var i, x;
    for (i = 0; i < _engine._outs.length; i++) {
      x = _engine._outs[i];
      x.engine = _engine;
      _engine._allOuts[x.name] = x;
      _jzz._info.outputs.push({
        id: x.name,
        name: x.name,
        manufacturer: x.manufacturer,
        version: x.version,
        engine: _engine._type
      });
      _outs.push(x);
    }
    for (i = 0; i < _virtual._outs.length; i++) {
      x = _virtual._outs[i];
      _jzz._info.outputs.push({
        id: x.name,
        name: x.name,
        manufacturer: x.manufacturer,
        version: x.version,
        engine: x.type
      });
      _outs.push(x);
    }
    for (i = 0; i < _engine._ins.length; i++) {
      x = _engine._ins[i];
      x.engine = _engine;
      _engine._allIns[x.name] = x;
      _jzz._info.inputs.push({
        id: x.name,
        name: x.name,
        manufacturer: x.manufacturer,
        version: x.version,
        engine: _engine._type
      });
      _ins.push(x);
    }
    for (i = 0; i < _virtual._ins.length; i++) {
      x = _virtual._ins[i];
      _jzz._info.inputs.push({
        id: x.name,
        name: x.name,
        manufacturer: x.manufacturer,
        version: x.version,
        engine: x.type
      });
      _ins.push(x);
    }
    if (_jzz._watcher && _jzz._watcher._handles.length) {
      var diff = _diff(_insW, _outsW, _jzz._info.inputs, _jzz._info.outputs);
       if (diff) {
        for (j = 0; j < diff.inputs.removed.length; j++) {
          x = _engine._inMap[diff.inputs.removed[j].name];
          if (x) x._closeAll();
        }
        for (j = 0; j < diff.outputs.removed.length; j++) {
          x = _engine._outMap[diff.outputs.removed[j].name];
          if (x) x._closeAll();
        }
        _fireW(diff);
      }
    }
    _insW = _jzz._info.inputs;
    _outsW = _jzz._info.outputs;
  }
  function _refresh() {
    if (!this._bad) _engine._refresh(this);
  }
  _J.prototype.refresh = function() {
    this._push(_refresh, []);
    return this._thenable();
  };

  function _filterList(q, arr) {
    var i, n;
    if (q instanceof Function) q = q(arr);
    if (!(q instanceof Array)) q = [q];
    var before = [];
    var after = [];
    var etc = arr.slice();
    var a = before;
    for (i = 0; i < q.length; i++) {
      if (typeof q[i] == 'undefined') a = after;
      else if (q[i] instanceof RegExp) for (n = 0; n < etc.length; n++) {
        if (q[i].test(etc[n].name)) {
          a.push(etc[n]);
          etc.splice(n, 1);
          n--;
        }
      }
      else {
        for (n = 0; n < etc.length; n++) if (q[i] + '' === n + '' || q[i] === etc[n].name || (q[i] instanceof Object && q[i].name === etc[n].name)) {
          a.push(etc[n]);
          etc.splice(n, 1);
          n--;
        }
      }
    }
    return a == before ? before : before.concat(etc).concat(after);
  }

  function _notFound(port, q) {
    var msg;
    if (q instanceof RegExp) msg = 'Port matching ' + q + ' not found';
    else if (q instanceof Object || typeof q == 'undefined') msg = 'Port not found';
    else msg = 'Port "' + q + '" not found';
    port._crash(msg);
  }
  function _openMidiOut(port, arg) {
    if (this._bad) port._crash(this._err());
    else {
      var arr = _filterList(arg, _outs);
      if (!arr.length) { _notFound(port, arg); return; }
      var pack = function(x) { return function() { x.engine._openOut(this, x.name); }; };
      for (var i = 0; i < arr.length; i++) arr[i] = pack(arr[i]);
      port._slip(_tryAny, [arr]);
      port._resume();
    }
  }
  _J.prototype.openMidiOut = function(arg) {
    var port = new _M();
    this._push(_refresh, []);
    this._push(_openMidiOut, [port, arg]);
    return port._thenable();
  };
  _J.prototype._openMidiOutNR = function(arg) {
    var port = new _M();
    this._push(_openMidiOut, [port, arg]);
    return port._thenable();
  };

  function _openMidiIn(port, arg) {
    if (this._bad) port._crash(this._err());
    else {
      var arr = _filterList(arg, _ins);
      if (!arr.length) { _notFound(port, arg); return; }
      var pack = function(x) { return function() { x.engine._openIn(this, x.name); }; };
      for (var i = 0; i < arr.length; i++) arr[i] = pack(arr[i]);
      port._slip(_tryAny, [arr]);
      port._resume();
    }
  }
  _J.prototype.openMidiIn = function(arg) {
    var port = new _M();
    this._push(_refresh, []);
    this._push(_openMidiIn, [port, arg]);
    return port._thenable();
  };
  _J.prototype._openMidiInNR = function(arg) {
    var port = new _M();
    this._push(_openMidiIn, [port, arg]);
    return port._thenable();
  };

  function _onChange(watcher, arg) {
    if (this._bad) watcher._crash();
    else {
      watcher._slip(_connectW, [arg]);
      watcher._resume();
    }
  }
  _J.prototype.onChange = function(arg) {
    if (!this._orig._watcher) this._orig._watcher = new _W();
    var watcher = this._orig._watcher._image();
    this._push(_onChange, [watcher, arg]);
    return watcher._thenable();
  };

  _J.prototype._close = function() {
    _engine._close();
  };

  // _M: MIDI-In/Out object
  function _M() {
    _R.apply(this);
    this._handles = [];
    this._outs = [];
  }
  _M.prototype = new _R();
  _M.prototype._filter = function(msg) {
    if (this._orig._mpe) {
      var out;
      var outs = 0;
      if (this._handles && this._handles.length) {
        outs = this._handles.length;
        out = this._handles[0];
      }
      if (this._outs && this._outs.length) {
        outs = this._outs.length;
        out = this._outs[0];
      }
      if (outs == 1 && !out._mpe) {
        msg = this._orig._mpe.filter(msg);
      }
    }
    return msg;
  };
  _M.prototype._receive = function(msg) { this._emit(this._filter(msg)); };
  function _receive(msg) { if (!this._bad) this._receive(msg); }
  _M.prototype.send = function() {
    this._push(_receive, [MIDI.apply(null, arguments)]);
    return this._thenable();
  };
  _M.prototype.note = function(c, n, v, t) {
    this.noteOn(c, n, v);
    if (t > 0) this.wait(t).noteOff(c, n);
    return this._thenable();
  };
  _M.prototype._emit = function(msg) {
    var i;
    for (i = 0; i < this._handles.length; i++) this._handles[i].apply(this, [MIDI(msg)._stamp(this)]);
    for (i = 0; i < this._outs.length; i++) {
      var m = MIDI(msg);
      if (!m._stamped(this._outs[i])) this._outs[i].send(m._stamp(this));
    }
  };
  function _emit(msg) { this._emit(msg); }
  _M.prototype.emit = function(msg) {
    this._push(_emit, [msg]);
    return this._thenable();
  };
  function _connect(arg) {
    if (arg instanceof Function) _push(this._orig._handles, arg);
    else _push(this._orig._outs, arg);
  }
  function _disconnect(arg) {
    if (typeof arg == 'undefined') {
      this._orig._handles = [];
      this._orig._outs = [];
    }
    else if (arg instanceof Function) _pop(this._orig._handles, arg);
    else _pop(this._orig._outs, arg);
  }
  _M.prototype.connect = function(arg) {
    this._push(_connect, [arg]);
    return this._thenable();
  };
  _M.prototype.disconnect = function(arg) {
    this._push(_disconnect, [arg]);
    return this._thenable();
  };
  _M.prototype.connected = function() {
    return this._orig._handles.length + this._orig._outs.length;
  };
  _M.prototype.ch = function(n) {
    if (typeof n == 'undefined') return this;
    _validateChannel(n);
    var chan = new _C(this, n);
    this._push(_kick, [chan]);
    return chan._thenable();
  };
  function _mpe(m, n) {
    if (!this._orig._mpe) this._orig._mpe = new MPE();
    this._orig._mpe.setup(m, n);
  }
  _M.prototype.mpe = function(m, n) {
    if (typeof m == 'undefined' && typeof n == 'undefined') return this;
    MPE.validate(m, n);
    var chan = n ? new _E(this, m, n) : new _C(this, m);
    this._push(_mpe, [m, n]);
    this._push(_kick, [chan]);
    return chan._thenable();
  };
  function _validateChannel(c) {
    if (c != parseInt(c) || c < 0 || c > 15)
      throw RangeError('Bad channel value (must not be less than 0 or more than 15): ' + c);
  }

  // _C: MIDI Channel object
  function _C(port, chan) {
    _M.apply(this);
    this._port = port._orig;
    this._chan = chan;
    _rechain(this, this._port, 'ch');
    _rechain(this, this._port, 'mpe');
    _rechain(this, this._port, 'connect');
    _rechain(this, this._port, 'disconnect');
    _rechain(this, this._port, 'close');
  }
  _C.prototype = new _M();
  _C.prototype.channel = function() { return this._chan; };
  _C.prototype._receive = function(msg) { this._port._receive(msg); };
  _C.prototype.note = function(n, v, t) {
    this.noteOn(n, v);
    if (t) this.wait(t).noteOff(n);
    return this._thenable();
  };

  // _E: MPE Channel object
  function _E(port, m, n) {
    _M.apply(this);
    this._port = port._orig;
    this._master = m;
    this._band = n;
    _rechain(this, this._port, 'ch');
    _rechain(this, this._port, 'mpe');
    _rechain(this, this._port, 'connect');
    _rechain(this, this._port, 'disconnect');
    _rechain(this, this._port, 'close');
  }
  _E.prototype = new _M();
  _E.prototype.channel = function() { return this._master; };
  _E.prototype._receive = function(msg) { this._port._receive(msg); };
  _E.prototype.note = function(n, v, t) {
    this.noteOn(n, v);
    if (t) this.wait(t).noteOff(n);
    return this._thenable();
  };

  // _W: Watcher object ~ MIDIAccess.onstatechange
  function _W() {
    _R.apply(this);
    this._handles = [];
    _rechain(this, _jzz, 'refresh');
    _rechain(this, _jzz, 'openMidiOut');
    _rechain(this, _jzz, 'openMidiIn');
    _rechain(this, _jzz, 'onChange');
    _rechain(this, _jzz, 'close');
  }
  _W.prototype = new _R();
  function _connectW(arg) {
    if (arg instanceof Function) {
      if (!this._orig._handles.length) _engine._watch();
      _push(this._orig._handles, arg);
    }
  }
  function _disconnectW(arg) {
    if (typeof arg == 'undefined') this._orig._handles = [];
    else _pop(this._orig._handles, arg);
    if (!this._orig._handles.length) _engine._unwatch();
  }
  _W.prototype.connect = function(arg) {
    this._push(_connectW, [arg]);
    return this._thenable();
  };
  _W.prototype.disconnect = function(arg) {
    this._push(_disconnectW, [arg]);
    return this._thenable();
  };
  function _changed(x0, y0, x1, y1) {
    var i;
    if (x0.length != x1.length || y0.length != y1.length) return true;
    for (i = 0; i < x0.length; i++) if (x0[i].name != x1[i].name) return true;
    for (i = 0; i < y0.length; i++) if (y0[i].name != y1[i].name) return true;
    return false;
  }
  function _diff(x0, y0, x1, y1) {
    if (!_changed(x0, y0, x1, y1)) return;
    var ax = []; // added
    var ay = [];
    var rx = []; // removed
    var ry = [];
    var i;
    var h = {};
    for (i = 0; i < x0.length; i++) h[x0[i].name] = true;
    for (i = 0; i < x1.length; i++) if (!h[x1[i].name]) ax.push(x1[i]);
    h = {};
    for (i = 0; i < x1.length; i++) h[x1[i].name] = true;
    for (i = 0; i < x0.length; i++) if (!h[x0[i].name]) rx.push(x0[i]);
    h = {};
    for (i = 0; i < y0.length; i++) h[y0[i].name] = true;
    for (i = 0; i < y1.length; i++) if (!h[y1[i].name]) ay.push(y1[i]);
    h = {};
    for (i = 0; i < y1.length; i++) h[y1[i].name] = true;
    for (i = 0; i < y0.length; i++) if (!h[y0[i].name]) ry.push(y0[i]);
    return { inputs: { added: ax, removed: rx }, outputs: { added: ay, removed: ry } };
  }
  function _fireW(arg) {
    for (i = 0; i < _jzz._watcher._handles.length; i++) _jzz._watcher._handles[i].apply(_jzz, [arg]);
  }

  var _jzz;
  var _engine = {};
  var _virtual = { _outs: [], _ins: []};

  // Node.js
  function _tryNODE() {
    if (typeof module != 'undefined' && module.exports) {
      _initNode(require('jazz-midi'));
      return;
    }
    this._break();
  }
  // Jazz-Plugin
  function _tryJazzPlugin() {
    var div = document.createElement('div');
    div.style.visibility = 'hidden';
    document.body.appendChild(div);
    var obj = document.createElement('object');
    obj.style.visibility = 'hidden';
    obj.style.width = '0px'; obj.style.height = '0px';
    obj.classid = 'CLSID:1ACE1618-1C7D-4561-AEE1-34842AA85E90';
    obj.type = 'audio/x-jazz';
    document.body.appendChild(obj);
    if (obj.isJazz) {
      _initJazzPlugin(obj);
      return;
    }
    this._break();
  }

  // Web MIDI API
  var _navigator;
  var _requestMIDIAccess;
  if (typeof navigator !== 'undefined' && navigator.requestMIDIAccess) {
    _navigator = navigator;
    _requestMIDIAccess = navigator.requestMIDIAccess;
    try {
      if (_requestMIDIAccess.toString().indexOf('JZZ(') != -1) _requestMIDIAccess = undefined;
    }
    catch (err) {}
  }
  function _tryWebMIDI() {
    if (_requestMIDIAccess) {
      var self = this;
      var onGood = function(midi) {
        _initWebMIDI(midi);
        self._resume();
      };
      var onBad = function(msg) {
        self._crash(msg);
      };
      var opt = {};
      _requestMIDIAccess.call(_navigator, opt).then(onGood, onBad);
      this._pause();
      return;
    }
    this._break();
  }
  function _tryWebMIDIsysex() {
    if (_requestMIDIAccess) {
      var self = this;
      var onGood = function(midi) {
        _initWebMIDI(midi, true);
        self._resume();
      };
      var onBad = function(msg) {
        self._crash(msg);
      };
      var opt = {sysex:true};
      _requestMIDIAccess.call(_navigator, opt).then(onGood, onBad);
      this._pause();
      return;
    }
    this._break();
  }
  // Web-extension
  function _tryCRX() {
    var self = this;
    var inst;
    var msg;
    function eventHandle() {
      inst = true;
      if (!msg) msg = document.getElementById('jazz-midi-msg');
      if (!msg) return;
      var a = [];
      try { a = JSON.parse(msg.innerText); } catch (err) {}
      msg.innerText = '';
      document.removeEventListener('jazz-midi-msg', eventHandle);
      if (a[0] === 'version') {
        _initCRX(msg, a[2]);
        self._resume();
      }
      else {
        self._crash();
      }
    }
    this._pause();
    document.addEventListener('jazz-midi-msg', eventHandle);
    try { document.dispatchEvent(new Event('jazz-midi')); } catch (err) {}
    _schedule(function() { if (!inst) self._crash(); });
  }

  function _zeroBreak() {
    this._pause();
    var self = this;
    _schedule(function() { self._crash(); });
  }

  function _filterEngines(opt) {
    var ret = [];
    var arr = _filterEngineNames(opt);
    for (var i = 0; i < arr.length; i++) {
      if (arr[i] == 'webmidi') {
        if (opt && opt.sysex === true) ret.push(_tryWebMIDIsysex);
        if (!opt || opt.sysex !== true || opt.degrade === true) ret.push(_tryWebMIDI);
      }
      else if (arr[i] == 'node') { ret.push(_tryNODE); ret.push(_zeroBreak); }
      else if (arr[i] == 'extension') ret.push(_tryCRX);
      else if (arr[i] == 'plugin') ret.push(_tryJazzPlugin);
    }
    ret.push(_initNONE);
    return ret;
  }

  function _filterEngineNames(opt) {
    var web = ['node', 'extension', 'plugin', 'webmidi'];
    if (!opt || !opt.engine) return web;
    var arr = opt.engine instanceof Array ? opt.engine : [opt.engine];
    var dup = {};
    var none;
    var etc;
    var head = [];
    var tail = [];
    var i;
    for (i = 0; i < arr.length; i++) {
      var name = arr[i].toString().toLowerCase();
      if (dup[name]) continue;
      dup[name] = true;
      if (name === 'none') none = true;
      if (name === 'etc' || typeof name == 'undefined') etc = true;
      if (etc) tail.push(name); else head.push(name);
      _pop(web, name);
    }
    if (etc || head.length || tail.length) none = false;
    return none ? [] : head.concat(etc ? web : tail);
  }

  function _initJZZ(opt) {
    _initAudioContext();
    _jzz = new _J();
    _jzz._options = opt;
    _jzz._push(_tryAny, [_filterEngines(opt)]);
    _jzz.refresh();
    _jzz._resume();
  }

  function _initNONE() {
    _engine._type = 'none';
    _engine._version = _version;
    _engine._sysex = true;
    _engine._outs = [];
    _engine._ins = [];
    _engine._refresh = function() { _postRefresh(); };
    _engine._watch = function() {};
    _engine._unwatch = function() {};
    _engine._close = function() {};
  }
  // common initialization for Jazz-Plugin and jazz-midi
  function _initEngineJP() {
    _engine._inArr = [];
    _engine._outArr = [];
    _engine._inMap = {};
    _engine._outMap = {};
    _engine._outsW = [];
    _engine._insW = [];
    _engine._version = _engine._main.version;
    _engine._sysex = true;
    var watcher;
    function _closeAll() {
      for (var i = 0; i < this.clients.length; i++) this._close(this.clients[i]);
    }
    _engine._refresh = function() {
      _engine._outs = [];
      _engine._ins = [];
      var i, x;
      for (i = 0; (x = _engine._main.MidiOutInfo(i)).length; i++) {
        _engine._outs.push({ type: _engine._type, name: x[0], manufacturer: x[1], version: x[2] });
      }
      for (i = 0; (x = _engine._main.MidiInInfo(i)).length; i++) {
        _engine._ins.push({ type: _engine._type, name: x[0], manufacturer: x[1], version: x[2] });
      }
      _postRefresh();
    };
    _engine._openOut = function(port, name) {
      var impl = _engine._outMap[name];
      if (!impl) {
        if (_engine._pool.length <= _engine._outArr.length) _engine._pool.push(_engine._newPlugin());
        impl = {
          name: name,
          clients: [],
          info: {
            name: name,
            manufacturer: _engine._allOuts[name].manufacturer,
            version: _engine._allOuts[name].version,
            type: 'MIDI-out',
            sysex: _engine._sysex,
            engine: _engine._type
          },
          _close: function(port) { _engine._closeOut(port); },
          _closeAll: _closeAll,
          _receive: function(a) { if (a.length) this.plugin.MidiOutRaw(a.slice()); }
        };
        var plugin = _engine._pool[_engine._outArr.length];
        impl.plugin = plugin;
        _engine._outArr.push(impl);
        _engine._outMap[name] = impl;
      }
      if (!impl.open) {
        var s = impl.plugin.MidiOutOpen(name);
        if (s !== name) {
          if (s) impl.plugin.MidiOutClose();
          port._break(); return;
        }
        impl.open = true;
      }
      port._orig._impl = impl;
      _push(impl.clients, port._orig);
      port._info = impl.info;
      port._receive = function(arg) { impl._receive(arg); };
      port._close = function() { impl._close(this); };
    };
    _engine._openIn = function(port, name) {
      var impl = _engine._inMap[name];
      if (!impl) {
        if (_engine._pool.length <= _engine._inArr.length) _engine._pool.push(_engine._newPlugin());
        impl = {
          name: name,
          clients: [],
          info: {
            name: name,
            manufacturer: _engine._allIns[name].manufacturer,
            version: _engine._allIns[name].version,
            type: 'MIDI-in',
            sysex: _engine._sysex,
            engine: _engine._type
          },
          _close: function(port) { _engine._closeIn(port); },
          _closeAll: _closeAll,
          handle: function(t, a) {
            for (var i = 0; i < this.clients.length; i++) {
              var msg = MIDI(a);
              this.clients[i]._emit(msg);
            }
          }
        };
        var makeHandle = function(x) { return function(t, a) { x.handle(t, a); }; };
        impl.onmidi = makeHandle(impl);
        var plugin = _engine._pool[_engine._inArr.length];
        impl.plugin = plugin;
        _engine._inArr.push(impl);
        _engine._inMap[name] = impl;
      }
      if (!impl.open) {
        var s = impl.plugin.MidiInOpen(name, impl.onmidi);
        if (s !== name) {
          if (s) impl.plugin.MidiInClose();
          port._break(); return;
        }
        impl.open = true;
      }
      port._orig._impl = impl;
      _push(impl.clients, port._orig);
      port._info = impl.info;
      port._close = function() { impl._close(this); };
    };
    _engine._closeOut = function(port) {
      var impl = port._impl;
      _pop(impl.clients, port._orig);
      if (!impl.clients.length && impl.open) {
        impl.open = false;
        impl.plugin.MidiOutClose();
      }
    };
    _engine._closeIn = function(port) {
      var impl = port._impl;
      _pop(impl.clients, port._orig);
      if (!impl.clients.length && impl.open) {
        impl.open = false;
        impl.plugin.MidiInClose();
      }
    };
    _engine._close = function() {
      for (var i = 0; i < _engine._inArr.length; i++) if (_engine._inArr[i].open) _engine._inArr[i].plugin.MidiInClose();
      _engine._unwatch();
    };
    _engine._watch = function() {
      if (!watcher) watcher = setInterval(function() { _engine._refresh(); }, 250);
    };
    _engine._unwatch = function() {
      if (watcher) clearInterval(watcher);
      watcher = undefined;
    };
  }

  function _initNode(obj) {
    _engine._type = 'node';
    _engine._main = obj;
    _engine._pool = [];
    _engine._newPlugin = function() { return new obj.MIDI(); };
    _initEngineJP();
  }
  function _initJazzPlugin(obj) {
    _engine._type = 'plugin';
    _engine._main = obj;
    _engine._pool = [obj];
    _engine._newPlugin = function() {
      var plg = document.createElement('object');
      plg.style.visibility = 'hidden';
      plg.style.width = '0px'; obj.style.height = '0px';
      plg.classid = 'CLSID:1ACE1618-1C7D-4561-AEE1-34842AA85E90';
      plg.type = 'audio/x-jazz';
      document.body.appendChild(plg);
      return plg.isJazz ? plg : undefined;
    };
    _initEngineJP();
  }
  function _initWebMIDI(access, sysex) {
    _engine._type = 'webmidi';
    _engine._version = 43;
    _engine._sysex = !!sysex;
    _engine._access = access;
    _engine._inMap = {};
    _engine._outMap = {};
    _engine._outsW = [];
    _engine._insW = [];
    var watcher;
    function _closeAll() {
      for (var i = 0; i < this.clients.length; i++) this._close(this.clients[i]);
    }
    _engine._refresh = function() {
      _engine._outs = [];
      _engine._ins = [];
      _engine._access.outputs.forEach(function(port) {
        _engine._outs.push({type: _engine._type, name: port.name, manufacturer: port.manufacturer, version: port.version});
      });
      _engine._access.inputs.forEach(function(port) {
        _engine._ins.push({type: _engine._type, name: port.name, manufacturer: port.manufacturer, version: port.version});
      });
      _postRefresh();
    };
    _engine._openOut = function(port, name) {
      var impl = _engine._outMap[name];
      if (!impl) {
        impl = {
          name: name,
          clients: [],
          info: {
            name: name,
            manufacturer: _engine._allOuts[name].manufacturer,
            version: _engine._allOuts[name].version,
            type: 'MIDI-out',
            sysex: _engine._sysex,
            engine: _engine._type
          },
          _close: function(port) { _engine._closeOut(port); },
          _closeAll: _closeAll,
          _receive: function(a) { if (impl.dev && a.length) this.dev.send(a.slice()); }
        };
      }
      var found;
      _engine._access.outputs.forEach(function(dev) {
        if (dev.name === name) found = dev;
      });
      if (found) {
        impl.dev = found;
        _engine._outMap[name] = impl;
        port._orig._impl = impl;
        _push(impl.clients, port._orig);
        port._info = impl.info;
        port._receive = function(arg) { impl._receive(arg); };
        port._close = function() { impl._close(this); };
        if (impl.dev.open) {
          port._pause();
          impl.dev.open().then(function() {
            port._resume();
          }, function() {
            port._crash();
          });
        }
      }
      else port._break();
    };
    _engine._openIn = function(port, name) {
      var impl = _engine._inMap[name];
      if (!impl) {
        impl = {
          name: name,
          clients: [],
          info: {
            name: name,
            manufacturer: _engine._allIns[name].manufacturer,
            version: _engine._allIns[name].version,
            type: 'MIDI-in',
            sysex: _engine._sysex,
            engine: _engine._type
          },
          _close: function(port) { _engine._closeIn(port); },
          _closeAll: _closeAll,
          handle: function(evt) {
            for (var i = 0; i < this.clients.length; i++) {
              var msg = MIDI([].slice.call(evt.data));
              this.clients[i]._emit(msg);
            }
          }
        };
      }
      var found;
      _engine._access.inputs.forEach(function(dev) {
        if (dev.name === name) found = dev;
      });
      if (found) {
        impl.dev = found;
        var makeHandle = function(x) { return function(evt) { x.handle(evt); }; };
        impl.dev.onmidimessage = makeHandle(impl);
        _engine._inMap[name] = impl;
        port._orig._impl = impl;
        _push(impl.clients, port._orig);
        port._info = impl.info;
        port._close = function() { impl._close(this); };
        if (impl.dev.open) {
          port._pause();
          impl.dev.open().then(function() {
            port._resume();
          }, function() {
            port._crash();
          });
        }
      }
      else port._break();
    };
    _engine._closeOut = function(port) {
      var impl = port._impl;
      _pop(impl.clients, port._orig);
      if (!impl.clients.length) {
        if (impl.dev && impl.dev.close) impl.dev.close();
        impl.dev = undefined;
      }
    };
    _engine._closeIn = function(port) {
      var impl = port._impl;
      _pop(impl.clients, port._orig);
      if (!impl.clients.length) {
        if (impl.dev) {
          impl.dev.onmidimessage = null;
          if (impl.dev.close) impl.dev.close();
        }
        impl.dev = undefined;
      }
    };
    _engine._close = function() {
      _engine._unwatch();
    };
    _engine._watch = function() {
      _engine._access.onstatechange = function() {
        watcher = true;
        _schedule(function() {
          if (watcher) {
            _engine._refresh();
            watcher = false;
          }
        });
      };
    };
    _engine._unwatch = function() {
      _engine._access.onstatechange = undefined;
    };
  }
  function _initCRX(msg, ver) {
    _engine._type = 'extension';
    _engine._version = ver;
    _engine._sysex = true;
    _engine._pool = [];
    _engine._outs = [];
    _engine._ins = [];
    _engine._inArr = [];
    _engine._outArr = [];
    _engine._inMap = {};
    _engine._outMap = {};
    _engine._outsW = [];
    _engine._insW = [];
    _engine.refreshClients = [];
    _engine._msg = msg;
    _engine._newPlugin = function() {
      var plugin = { id: _engine._pool.length };
      _engine._pool.push(plugin);
      if (!plugin.id) plugin.ready = true;
      else document.dispatchEvent(new CustomEvent('jazz-midi', {detail:['new']}));
    };
    _engine._newPlugin();
    _engine._refresh = function(client) {
      _engine.refreshClients.push(client);
      client._pause();
      _schedule(function() {
        document.dispatchEvent(new CustomEvent('jazz-midi', { detail: ['refresh'] }));
      });
    };
    function _closeAll() {
      for (var i = 0; i < this.clients.length; i++) this._close(this.clients[i]);
    }
    _engine._openOut = function(port, name) {
      var impl = _engine._outMap[name];
      if (!impl) {
        if (_engine._pool.length <= _engine._outArr.length) _engine._newPlugin();
        var plugin = _engine._pool[_engine._outArr.length];
        impl = {
          name: name,
          clients: [],
          info: {
            name: name,
            manufacturer: _engine._allOuts[name].manufacturer,
            version: _engine._allOuts[name].version,
            type: 'MIDI-out',
            sysex: _engine._sysex,
            engine: _engine._type
          },
          _start: function() { document.dispatchEvent(new CustomEvent('jazz-midi', { detail: ['openout', plugin.id, name] })); },
          _close: function(port) { _engine._closeOut(port); },
          _closeAll: _closeAll,
          _receive: function(a) { if (a.length) { var v = a.slice(); v.splice(0, 0, 'play', plugin.id); document.dispatchEvent(new CustomEvent('jazz-midi', {detail: v})); } }
        };
        impl.plugin = plugin;
        plugin.output = impl;
        _engine._outArr.push(impl);
        _engine._outMap[name] = impl;
      }
      port._orig._impl = impl;
      _push(impl.clients, port._orig);
      port._info = impl.info;
      port._receive = function(arg) { impl._receive(arg); };
      port._close = function() { impl._close(this); };
      if (!impl.open) {
        port._pause();
        if (impl.plugin.ready) impl._start();
      }
    };
    _engine._openIn = function(port, name) {
      var impl = _engine._inMap[name];
      if (!impl) {
        if (_engine._pool.length <= _engine._inArr.length) _engine._newPlugin();
        var plugin = _engine._pool[_engine._inArr.length];
        impl = {
          name: name,
          clients: [],
          info: {
            name: name,
            manufacturer: _engine._allIns[name].manufacturer,
            version: _engine._allIns[name].version,
            type: 'MIDI-in',
            sysex: _engine._sysex,
            engine: _engine._type
          },
          _start: function() { document.dispatchEvent(new CustomEvent('jazz-midi', { detail: ['openin', plugin.id, name] })); },
          _close: function(port) { _engine._closeIn(port); },
          _closeAll: _closeAll
        };
        impl.plugin = plugin;
        plugin.input = impl;
        _engine._inArr.push(impl);
        _engine._inMap[name] = impl;
      }
      port._orig._impl = impl;
      _push(impl.clients, port._orig);
      port._info = impl.info;
      port._close = function() { impl._close(this); };
      if (!impl.open) {
        port._pause();
        if (impl.plugin.ready) impl._start();
      }
    };
    _engine._closeOut = function(port) {
      var impl = port._impl;
      _pop(impl.clients, port._orig);
      if (!impl.clients.length && impl.open) {
        impl.open = false;
        document.dispatchEvent(new CustomEvent('jazz-midi', { detail: ['closeout', impl.plugin.id] }));
      }
    };
    _engine._closeIn = function(port) {
      var impl = port._impl;
      _pop(impl.clients, port._orig);
      if (!impl.clients.length && impl.open) {
        impl.open = false;
        document.dispatchEvent(new CustomEvent('jazz-midi', { detail: ['closein', impl.plugin.id] }));
      }
    };
    _engine._close = function() {
      _engine._unwatch();
    };
    var watcher;
    _engine._watch = function() {
      _engine._insW = _engine._ins;
      _engine._outsW = _engine._outs;
      watcher = setInterval(function() {
        document.dispatchEvent(new CustomEvent('jazz-midi', {detail:['refresh']}));
      }, 250);
    };
    _engine._unwatch = function() {
      clearInterval(watcher);
      watcher = undefined;
    };
    document.addEventListener('jazz-midi-msg', function() {
      var v = _engine._msg.innerText.split('\n');
      var impl, i, j;
      _engine._msg.innerText = '';
      for (i = 0; i < v.length; i++) {
        var a = [];
        try { a = JSON.parse(v[i]); } catch (err) {}
        if (!a.length) continue;
        if (a[0] === 'refresh') {
          if (a[1].ins) {
            for (j = 0; j < a[1].ins.length; j++) a[1].ins[j].type = _engine._type;
            _engine._ins = a[1].ins;
          }
          if (a[1].outs) {
            for (j = 0; j < a[1].outs.length; j++) a[1].outs[j].type = _engine._type;
            _engine._outs = a[1].outs;
          }
          _postRefresh();
          for (j = 0; j < _engine.refreshClients.length; j++) _engine.refreshClients[j]._resume();
          _engine.refreshClients = [];
        }
        else if (a[0] === 'version') {
          var plugin = _engine._pool[a[1]];
          if (plugin) {
            plugin.ready = true;
            if (plugin.input) plugin.input._start();
            if (plugin.output) plugin.output._start();
          }
        }
        else if (a[0] === 'openout') {
          impl = _engine._pool[a[1]].output;
          if (impl) {
            if (a[2] == impl.name) {
              impl.open = true;
              if (impl.clients) for (j = 0; j < impl.clients.length; j++) impl.clients[j]._resume();
            }
            else if (impl.clients) for (j = 0; j < impl.clients.length; j++) impl.clients[j]._crash();
          }
        }
        else if (a[0] === 'openin') {
          impl = _engine._pool[a[1]].input;
          if (impl) {
            if (a[2] == impl.name) {
              impl.open = true;
              if (impl.clients) for (j = 0; j < impl.clients.length; j++) impl.clients[j]._resume();
            }
            else if (impl.clients) for (j = 0; j < impl.clients.length; j++) impl.clients[j]._crash();
          }
        }
        else if (a[0] === 'midi') {
          impl = _engine._pool[a[1]].input;
          if (impl && impl.clients) {
            for (j = 0; j < impl.clients.length; j++) {
              var msg = MIDI(a.slice(3));
              impl.clients[j]._emit(msg);
            }
          }
        }
      }
    });
  }

  var JZZ = function(opt) {
    if (!_jzz) _initJZZ(opt);
    return _jzz._thenable();
  };
  JZZ.JZZ = JZZ;
  JZZ.info = function() { return _J.prototype.info(); };
  JZZ.Widget = function(arg) {
    var obj = new _M();
    if (arg instanceof Object) for (var k in arg) if (arg.hasOwnProperty(k)) obj[k] = arg[k];
    obj._resume();
    return obj;
  };
  _J.prototype.Widget = JZZ.Widget;

  // JZZ.SMPTE

  function SMPTE() {
    var self = this instanceof SMPTE ? this : self = new SMPTE();
    SMPTE.prototype.reset.apply(self, arguments);
    return self;
  }
  SMPTE.prototype.reset = function(arg) {
    if (arg instanceof SMPTE) {
      this.setType(arg.getType());
      this.setHour(arg.getHour());
      this.setMinute(arg.getMinute());
      this.setSecond(arg.getSecond());
      this.setFrame(arg.getFrame());
      this.setQuarter(arg.getQuarter());
      return this;
    }
    var arr = arg instanceof Array ? arg : arguments;
    this.setType(arr[0]);
    this.setHour(arr[1]);
    this.setMinute(arr[2]);
    this.setSecond(arr[3]);
    this.setFrame(arr[4]);
    this.setQuarter(arr[5]);
    return this;
  };
  function _fixDropFrame() { if (this.type == 29.97 && !this.second && this.frame < 2 && this.minute % 10) this.frame = 2; }
  SMPTE.prototype.isFullFrame = function() { return this.quarter == 0 || this.quarter == 4; };
  SMPTE.prototype.getType = function() { return this.type; };
  SMPTE.prototype.getHour = function() { return this.hour; };
  SMPTE.prototype.getMinute = function() { return this.minute; };
  SMPTE.prototype.getSecond = function() { return this.second; };
  SMPTE.prototype.getFrame = function() { return this.frame; };
  SMPTE.prototype.getQuarter = function() { return this.quarter; };
  SMPTE.prototype.setType = function(x) {
    if (typeof x == 'undefined' || x == 24) this.type = 24;
    else if (x == 25) this.type = 25;
    else if (x == 29.97) { this.type = 29.97; _fixDropFrame.apply(this); }
    else if (x == 30) this.type = 30;
    else throw RangeError('Bad SMPTE frame rate: ' + x);
    if (this.frame >= this.type) this.frame = this.type - 1; // could not be more than 29
    return this;
  };
  SMPTE.prototype.setHour = function(x) {
    if (typeof x == 'undefined') x = 0;
    if (x != parseInt(x) || x < 0 || x >= 24) throw RangeError('Bad SMPTE hours value: ' + x);
    this.hour = x;
    return this;
  };
  SMPTE.prototype.setMinute = function(x) {
    if (typeof x == 'undefined') x = 0;
    if (x != parseInt(x) || x < 0 || x >= 60) throw RangeError('Bad SMPTE minutes value: ' + x);
    this.minute = x;
    _fixDropFrame.apply(this);
    return this;
  };
  SMPTE.prototype.setSecond = function(x) {
    if (typeof x == 'undefined') x = 0;
    if (x != parseInt(x) || x < 0 || x >= 60) throw RangeError('Bad SMPTE seconds value: ' + x);
    this.second = x;
    _fixDropFrame.apply(this);
    return this;
  };
  SMPTE.prototype.setFrame = function(x) {
    if (typeof x == 'undefined') x = 0;
    if (x != parseInt(x) || x < 0 || x >= this.type) throw RangeError('Bad SMPTE frame number: ' + x);
    this.frame = x;
    _fixDropFrame.apply(this);
    return this;
  };
  SMPTE.prototype.setQuarter = function(x) {
    if (typeof x == 'undefined') x = 0;
    if (x != parseInt(x) || x < 0 || x >= 8) throw RangeError('Bad SMPTE quarter frame: ' + x);
    this.quarter = x;
    return this;
  };
  SMPTE.prototype.incrFrame = function() {
    this.frame++;
    if (this.frame >= this.type) {
      this.frame = 0;
      this.second++;
      if (this.second >= 60) {
        this.second = 0;
        this.minute++;
        if (this.minute >= 60) {
          this.minute = 0;
          this.hour = this.hour >= 23 ? 0 : this.hour + 1;
        }
      }
    }
    _fixDropFrame.apply(this);
    return this;
  };
  SMPTE.prototype.decrFrame = function() {
    if (!this.second && this.frame == 2 && this.type == 29.97 && this.minute % 10) this.frame = 0; // drop-frame
    this.frame--;
    if (this.frame < 0) {
      this.frame = this.type == 29.97 ? 29 : this.type - 1;
      this.second--;
      if (this.second < 0) {
        this.second = 59;
        this.minute--;
        if (this.minute < 0) {
          this.minute = 59;
          this.hour = this.hour ? this.hour - 1 : 23;
        }
      }
    }
    return this;
  };
  SMPTE.prototype.incrQF = function() {
    this.backwards = false;
    this.quarter = (this.quarter + 1) & 7;
    if (this.quarter == 0 || this.quarter == 4) this.incrFrame();
    return this;
  };
  SMPTE.prototype.decrQF = function() {
    this.backwards = true;
    this.quarter = (this.quarter + 7) & 7;
    if (this.quarter == 3 || this.quarter == 7) this.decrFrame();
    return this;
  };
  function _825(a) { return [[24, 25, 29.97, 30][(a[7] >> 1) & 3], ((a[7] & 1) << 4) | a[6], (a[5] << 4) | a[4], (a[3] << 4) | a[2], (a[1] << 4) | a[0]]; }
  SMPTE.prototype.read = function(m) {
    if (!(m instanceof MIDI)) m = MIDI.apply(null, arguments);
    if (m[0] == 0xf0 && m[1] == 0x7f && m[3] == 1 && m[4] == 1 && m[9] == 0xf7) {
      this.type = [24, 25, 29.97, 30][(m[5] >> 5) & 3];
      this.hour = m[5] & 31;
      this.minute = m[6];
      this.second = m[7];
      this.frame = m[8];
      this.quarter = 0;
      this._ = undefined;
      this._b = undefined;
      this._f = undefined;
      return true;
    }
    if (m[0] == 0xf1 && typeof m[1] != 'undefined') {
      var q = m[1] >> 4;
      var n = m[1] & 15;
      if (q == 0) {
        if (this._ == 7) {
          if (this._f == 7) {
            this.reset(_825(this._a));
            this.incrFrame();
          }
          this.incrFrame();
        }
      }
      else if (q == 3) {
        if (this._ == 4) {
          this.decrFrame();
        }
      }
      else if (q == 4) {
        if (this._ == 3) {
          this.incrFrame();
        }
      }
      else if (q == 7) {
        if (this._ === 0) {
          if (this._b === 0) {
            this.reset(_825(this._a));
            this.decrFrame();
          }
          this.decrFrame();
        }
      }
      if (!this._a) this._a = [];
      this._a[q] = n;
      this._f = this._f === q - 1 || q == 0 ? q : undefined;
      this._b = this._b === q + 1 || q == 7 ? q : undefined;
      this._ = q;
      this.quarter = q;
      return true;
    }
    return false;
  };
  function _mtc(t) {
    if (!t.backwards && t.quarter >= 4) t.decrFrame(); // continue encoding previous frame
    else if (t.backwards && t.quarter < 4) t.incrFrame();
    var ret;
    switch (t.quarter >> 1) {
      case 0: ret = t.frame; break;
      case 1: ret = t.second; break;
      case 2: ret = t.minute; break;
      default: ret = t.hour;
    }
    if (t.quarter & 1) ret >>= 4;
    else ret &= 15;
    if (t.quarter == 7) {
      if (t.type == 25) ret |= 2;
      else if (t.type == 29.97) ret |= 4;
      else if (t.type == 30) ret |= 6;
    }
    // restore original t
    if (!t.backwards && t.quarter >= 4) t.incrFrame();
    else if (t.backwards && t.quarter < 4) t.decrFrame();
    return ret | (t.quarter << 4);
  }
  function _hrtype(t) {
    if (t.type == 25) return t.hour | 0x20;
    if (t.type == 29.97) return t.hour | 0x40;
    if (t.type == 30) return t.hour | 0x60;
    return t.hour;
  }
  function _dec(x) { return x < 10 ? '0' + x : x; }
  function _smptetxt(x) {
    var arr = [];
    for (var i = 0; i < x.length; i++) arr[i] = _dec(x[i]);
    return arr.join(':');
  }
  SMPTE.prototype.toString = function() { return _smptetxt([this.hour, this.minute, this.second, this.frame]); };
  JZZ.SMPTE = SMPTE;

  // JZZ.MIDI

  function MIDI(arg) {
    var self = this instanceof MIDI ? this : self = new MIDI();
    var i;
    if (arg instanceof MIDI) {
      self._from = arg._from.slice();
      for (i in arg) if (arg.hasOwnProperty(i) && i != '_from') self[i] = arg[i];
      return self;
    }
    else self._from = [];
    if (typeof arg == 'undefined') return self;
    var arr = arg instanceof Array ? arg : arguments;
    for (i = 0; i < arr.length; i++) {
      n = arr[i];
      if (i == 1) {
        if (self[0] >= 0x80 && self[0] <= 0xAF) n = MIDI.noteValue(n);
        if (self[0] >= 0xC0 && self[0] <= 0xCF) n = MIDI.programValue(n);
      }
      if (n != parseInt(n) || n < 0 || n > 255) _throw(arr[i]);
      self.push(n);
    }
    return self;
  }
  MIDI.prototype = [];
  MIDI.prototype.constructor = MIDI;
  var _noteNum = {};
  MIDI.noteValue = function(x) { return typeof x == 'undefined' ? undefined : _noteNum[x.toString().toLowerCase()]; };
  MIDI.programValue = function(x) { return x; };
  MIDI.freq = function(n, a) {
    if (typeof a == 'undefined') a = 440.0;
    return (a * Math.pow(2, (_7b(MIDI.noteValue(n), n) - 69.0) / 12.0));
  };

  var _noteMap = { c:0, d:2, e:4, f:5, g:7, a:9, b:11, h:11 };
  for (k in _noteMap) {
    if (!_noteMap.hasOwnProperty(k)) continue;
    for (n = 0; n < 12; n++) {
      m = _noteMap[k] + n * 12;
      if (m > 127) break;
      _noteNum[k+n] = m;
      if (m > 0) { _noteNum[k + 'b' + n] = m - 1; _noteNum[k + 'bb' + n] = m - 2; }
      if (m < 127) { _noteNum[k + '#' + n] = m + 1; _noteNum[k + '##' + n] = m + 2; }
    }
  }
  for (n = 0; n < 128; n++) _noteNum[n] = n;
  function _throw(x) { throw RangeError('Bad MIDI value: ' + x); }
  function _ch(c) { _validateChannel(c); return parseInt(c); }
  function _7b(n, m) { if (n != parseInt(n) || n < 0 || n > 0x7f) _throw(typeof m == 'undefined' ? n : m); return parseInt(n); }
  function _8b(n, m) { if (n != parseInt(n) || n < 0 || n > 0xff) _throw(typeof m == 'undefined' ? n : m); return parseInt(n); }
  function _lsb(n) { if (n != parseInt(n) || n < 0 || n > 0x3fff) _throw(n); return parseInt(n) & 0x7f; }
  function _msb(n) { if (n != parseInt(n) || n < 0 || n > 0x3fff) _throw(n); return parseInt(n) >> 7; }
  function _8bs(s) { s = '' + s; for (var i = 0; i < s.length; i++) if (s.charCodeAt(i) > 255) _throw(s[i]); return s; }
  var _helperCH = {
    noteOff: function(c, n, v) { if (typeof v == 'undefined') v = 64; return [0x80 + _ch(c), _7b(MIDI.noteValue(n), n), _7b(v)]; },
    noteOn: function(c, n, v) { if (typeof v == 'undefined') v = 127; return [0x90 + _ch(c), _7b(MIDI.noteValue(n), n), _7b(v)]; },
    aftertouch: function(c, n, v) { return [0xA0 + _ch(c), _7b(MIDI.noteValue(n), n), _7b(v)]; },
    control: function(c, n, v) { return [0xB0 + _ch(c), _7b(n), _7b(v)]; },
    program: function(c, n) { return [0xC0 + _ch(c), _7b(MIDI.programValue(n), n)]; },
    pressure: function(c, n) { return [0xD0 + _ch(c), _7b(n)]; },
    pitchBend: function(c, n) { return [0xE0 + _ch(c), _lsb(n), _msb(n)]; },
    bankMSB: function(c, n) { return [0xB0 + _ch(c), 0x00, _7b(n)]; },
    bankLSB: function(c, n) { return [0xB0 + _ch(c), 0x20, _7b(n)]; },
    modMSB: function(c, n) { return [0xB0 + _ch(c), 0x01, _7b(n)]; },
    modLSB: function(c, n) { return [0xB0 + _ch(c), 0x21, _7b(n)]; },
    breathMSB: function(c, n) { return [0xB0 + _ch(c), 0x02, _7b(n)]; },
    breathLSB: function(c, n) { return [0xB0 + _ch(c), 0x22, _7b(n)]; },
    footMSB: function(c, n) { return [0xB0 + _ch(c), 0x04, _7b(n)]; },
    footLSB: function(c, n) { return [0xB0 + _ch(c), 0x24, _7b(n)]; },
    portamentoMSB: function(c, n) { return [0xB0 + _ch(c), 0x05, _7b(n)]; },
    portamentoLSB: function(c, n) { return [0xB0 + _ch(c), 0x25, _7b(n)]; },
    volumeMSB: function(c, n) { return [0xB0 + _ch(c), 0x07, _7b(n)]; },
    volumeLSB: function(c, n) { return [0xB0 + _ch(c), 0x27, _7b(n)]; },
    balanceMSB: function(c, n) { return [0xB0 + _ch(c), 0x08, _7b(n)]; },
    balanceLSB: function(c, n) { return [0xB0 + _ch(c), 0x28, _7b(n)]; },
    panMSB: function(c, n) { return [0xB0 + _ch(c), 0x0A, _7b(n)]; },
    panLSB: function(c, n) { return [0xB0 + _ch(c), 0x2A, _7b(n)]; },
    expressionMSB: function(c, n) { return [0xB0 + _ch(c), 0x0B, _7b(n)]; },
    expressionLSB: function(c, n) { return [0xB0 + _ch(c), 0x2B, _7b(n)]; },
    damper: function(c, b) { return [0xB0 + _ch(c), 0x40, b ? 127 : 0]; },
    portamento: function(c, b) { return [0xB0 + _ch(c), 0x41, b ? 127 : 0]; },
    sostenuto: function(c, b) { return [0xB0 + _ch(c), 0x42, b ? 127 : 0]; },
    soft: function(c, b) { return [0xB0 + _ch(c), 0x43, b ? 127 : 0]; },
    allSoundOff: function(c) { return [0xB0 + _ch(c), 0x78, 0]; },
    allNotesOff: function(c) { return [0xB0 + _ch(c), 0x7b, 0]; },
  };
  var _helperNC = { // no channel
    mtc: function(t) { return [0xF1, _mtc(t)]; },
    songPosition: function(n) { return [0xF2, _lsb(n), _msb(n)]; },
    songSelect: function(n) { return [0xF3, _7b(n)]; },
    tune: function() { return [0xF6]; },
    clock: function() { return [0xF8]; },
    start: function() { return [0xFA]; },
    continue: function() { return [0xFB]; },
    stop: function() { return [0xFC]; },
    active: function() { return [0xFE]; },
    sxIdRequest: function() { return [0xF0, 0x7E, 0x7F, 0x06, 0x01, 0xF7]; },
    sxFullFrame: function(t) { return [0xF0, 0x7F, 0x7F, 0x01, 0x01, _hrtype(t), t.getMinute(), t.getSecond(), t.getFrame(), 0xF7]; },
    reset: function() { return [0xFF]; },
  };
  function _smf(ff, dd) {
    var midi = new MIDI();
    midi.ff = _8b(ff);
    midi.dd = typeof dd == 'undefined' ? '' : _8bs(dd);
    return midi;
  }
  var _helperSMF = { // Standard MIDI File events
    smf: function(arg) {
      if (arg instanceof MIDI) return new MIDI(arg);
      var arr = arg instanceof Array ? arg : arguments;
      var ff = _8b(arr[0]);
      var dd = '';
      if (arr.length == 2) dd = _2s(arr[1]);
      else if (arr.length > 2) dd = _2s(Array.prototype.slice.call(arr, 1));
      return _smf(ff, dd);
    },
    smfSeqNumber: function(dd) {
      if (dd == parseInt(dd)) {
        if (dd < 0 || dd > 0xffff) throw RangeError('Sequence number out of range: ' + dd);
        dd = String.fromCharCode(dd >> 8) + String.fromCharCode(dd & 0xff);
      }
      else {
        dd = '' + dd;
        if (dd.length == 0) dd = '\x00\x00';
        else if (dd.length == 1) dd = '\x00' + dd;
        else if (dd.length > 2) throw RangeError('Sequence number out of range: ' + _smftxt(dd));
      }
      return _smf(0, dd);
    },
    smfText: function(dd) { return _smf(1, JZZ.lib.toUTF8(dd)); },
    smfCopyright: function(dd) { return _smf(2, JZZ.lib.toUTF8(dd)); },
    smfSeqName: function(dd) { return _smf(3, JZZ.lib.toUTF8(dd)); },
    smfInstrName: function(dd) { return _smf(4, JZZ.lib.toUTF8(dd)); },
    smfLyric: function(dd) { return _smf(5, JZZ.lib.toUTF8(dd)); },
    smfMarker: function(dd) { return _smf(6, JZZ.lib.toUTF8(dd)); },
    smfCuePoint: function(dd) { return _smf(7, JZZ.lib.toUTF8(dd)); },
    smfProgName: function(dd) { return _smf(8, JZZ.lib.toUTF8(dd)); },
    smfDevName: function(dd) { return _smf(9, JZZ.lib.toUTF8(dd)); },
    smfChannelPrefix: function(dd) {
      if (dd == parseInt(dd)) {
        _validateChannel(dd);
        dd = String.fromCharCode(dd);
      }
      else {
        dd = '' + dd;
        if (dd.length == 0) dd = '\x00';
        else if (dd.length > 1 || dd.charCodeAt(0) > 15) throw RangeError('Channel number out of range: ' + _smftxt(dd));
      }
      return _smf(32, dd);
    },
    smfMidiPort: function(dd) {
      if (dd == parseInt(dd)) {
        if (dd < 0 || dd > 127) throw RangeError('Port number out of range: ' + dd);
        dd = String.fromCharCode(dd);
      }
      else {
        dd = '' + dd;
        if (dd.length == 0) dd = '\x00';
        else if (dd.length > 1 || dd.charCodeAt(0) > 127) throw RangeError('Port number out of range: ' + _smftxt(dd));
      }
      return _smf(33, dd);
    },
    smfEndOfTrack: function(dd) {
      if (_2s(dd) != '') throw RangeError('Unexpected data: ' + _smftxt(_2s(dd)));
      return _smf(47);
    },
    smfTempo: function(dd) { // microseconds per quarter note
      if (('' + dd).length == 3) return _smf(81, dd);
      if (dd == parseInt(dd) && dd > 0 && dd <= 0xffffff) {
        return _smf(81, String.fromCharCode(dd >> 16) + String.fromCharCode((dd >> 8) & 0xff) + String.fromCharCode(dd & 0xff));
      }
      throw RangeError('Out of range: ' + _smftxt(_2s(dd)));
    },
    smfBPM: function(bpm) { return _helperSMF.smfTempo(Math.round(60000000.0 / bpm)); },
    smfSMPTE: function(dd) {
      if (dd instanceof SMPTE) return _smf(84, String.fromCharCode(dd.hour) + String.fromCharCode(dd.minute) + String.fromCharCode(dd.second) + String.fromCharCode(dd.frame) + String.fromCharCode((dd.quarter % 4) * 25));
      var s = '' + dd;
      if (s.length == 5) {
        return _smf(84, dd);
      }
      var arr = dd instanceof Array ? dd : Array.prototype.slice.call(arguments);
      arr.splice(0, 0, 30);
      return _helperSMF.smfSMPTE(new SMPTE(arr));
    },
    smfTimeSignature: function(a, b, c, d) {
      var nn, dd, cc, bb;
      var m = ('' + a ).match(/^\s*(\d+)\s*\/\s*(\d+)\s*$/);
      if (m) {
        nn = parseInt(m[1]);
        dd = parseInt(m[2]);
        if (nn > 0 && nn <= 0xff && dd && !(dd & (dd - 1))) {
          cc = dd; dd = 0;
          for (cc >>= 1; cc; cc >>= 1) dd++;
          cc = b == parseInt(b) ? b : 24;
          bb = c == parseInt(c) ? c : 8;
          return _smf(88, String.fromCharCode(nn) + String.fromCharCode(dd) + String.fromCharCode(cc) + String.fromCharCode(bb));
        }
        else if (('' + a ).length == 4) return _smf(88, a);
      }
      else if (a == parseInt(a) && b == parseInt(b) && b && !(b & (b - 1))) {
        nn = a;
        dd = 0;
        cc = b;
        for (cc >>= 1; cc; cc >>= 1) dd++;
        cc = c == parseInt(c) ? c : 24;
        bb = d == parseInt(d) ? d : 8;
        return _smf(88, String.fromCharCode(nn) + String.fromCharCode(dd) + String.fromCharCode(cc) + String.fromCharCode(bb));
      }
      else if (('' + a ).length == 4) return _smf(88, a);
      throw RangeError('Wrong time signature: ' + _smftxt(_2s(a)));
    },
    smfKeySignature: function(dd) {
      dd = '' + dd;
      var m = dd.match(/^\s*([A-H][b#]?)\s*(|maj|major|dur|m|min|minor|moll)\s*$/i);
      if (m) {
        var sf = {
          CB: 0, GB: 1, DB: 2, AB: 3, EB: 4, BB: 5, F: 6, C: 7, G: 8, D: 9, A: 10,
          E:11, B: 12, H: 12, 'F#': 13, 'C#': 14, 'G#': 15, 'D#': 16, 'A#': 17
        }[m[1].toUpperCase()];
        var mi = { '': 0, MAJ: 0, MAJOR: 0, DUR: 0, M: 1, MIN: 1, MINOR: 1, MOLL: 1}[m[2].toUpperCase()];
        if (typeof sf != 'undefined' && typeof mi != 'undefined') {
          if (mi) sf -= 3;
          sf -= 7;
          if (sf >= -7 && sf < 0) dd = String.fromCharCode(256 + sf) + String.fromCharCode(mi);
          else if (sf >= 0 && sf <= 7) dd = String.fromCharCode(sf) + String.fromCharCode(mi);
        }
      }
      if (dd.length == 2 && dd.charCodeAt(1) <= 1 && (dd.charCodeAt(0) <= 7 || dd.charCodeAt(0) <= 255 && dd.charCodeAt(0) >= 249)) return _smf(89, dd);
      throw RangeError('Incorrect key signature: ' + _smftxt(dd));
    },
    smfSequencer: function(dd) { return _smf(127, _2s(dd)); }
  };

  function _copyPortHelper(M, name, func) {
    M.prototype[name] = function() { this.send(func.apply(0, arguments)); return this; };
  }
  function _copyChannelHelper(C, name, func) {
    C.prototype[name] = function() {
      this.send(func.apply(0, [this._chan].concat(Array.prototype.slice.call(arguments)))); return this;
    };
  }
  function _copyHelperNC(name, func) {
    MIDI[name] = function() { return new MIDI(func.apply(0, arguments)); };
  }
  function _copyHelperSMF(name, func) {
    MIDI[name] = function() { return func.apply(0, arguments); };
  }
  function _copyHelperCH(name, func) {
    _copyHelperNC(name, func);
    _E.prototype[name] = function() {
      var chan;
      var args = Array.prototype.slice.call(arguments);
      if (args.length < func.length) args = [this._master].concat(args);
      else {
        chan = _7b(MIDI.noteValue(args[0], args[0]));
        args[0] = this._master;
      }
      var msg = func.apply(0, args);
      msg.mpe = chan;
      this.send(msg);
      return this;
    };
  }
  for (k in _helperNC) if (_helperNC.hasOwnProperty(k)) _copyHelperNC(k, _helperNC[k]);
  for (k in _helperSMF) if (_helperSMF.hasOwnProperty(k)) _copyHelperSMF(k, _helperSMF[k]);
  for (k in _helperCH) if (_helperCH.hasOwnProperty(k)) _copyHelperCH(k, _helperCH[k]);
  function _copyMidiHelpers(M, C) {
    for (k in _helperNC) if (_helperNC.hasOwnProperty(k)) _copyPortHelper(M, k, _helperNC[k]);
    for (k in _helperSMF) if (_helperSMF.hasOwnProperty(k)) _copyPortHelper(M, k, _helperSMF[k]);
    for (k in _helperCH) if (_helperCH.hasOwnProperty(k)) _copyPortHelper(M, k, _helperCH[k]);
    if (C) for (k in _helperCH) if (_helperCH.hasOwnProperty(k)) _copyChannelHelper(C, k, _helperCH[k]);
  }
  _copyMidiHelpers(_M, _C);

  _E.prototype.noteOn = function(n, v) {
    var msg = MIDI.noteOn(this._master, n, v);
    msg._mpe = msg[1];
    this.send(msg);
    return this;
  };
  _E.prototype.noteOff = function(n, v) {
    var msg = MIDI.noteOff(this._master, n, v);
    msg._mpe = msg[1];
    this.send(msg);
    return this;
  };
  _E.prototype.aftertouch = function(n, v) {
    var msg = MIDI.aftertouch(this._master, n, v);
    msg._mpe = msg[1];
    this.send(msg);
    return this;
  };

  var _channelMap = { a:10, b:11, c:12, d:13, e:14, f:15, A:10, B:11, C:12, D:13, E:14, F:15 };
  for (k = 0; k < 16; k++) _channelMap[k] = k;
  MIDI.prototype.getChannel = function() {
    if (this.ff == 0x20 && this.dd.length == 1 && this.dd.charCodeAt(0) < 16) return this.dd.charCodeAt(0);
    var c = this[0];
    if (typeof c == 'undefined' || c < 0x80 || c > 0xef) return;
    return c & 15;
  };
  MIDI.prototype.setChannel = function(x) {
    x = _channelMap[x];
    if (typeof x == 'undefined') return this;
    if (this.ff == 0x20) this.dd = String.fromCharCode(x);
    else {
      var c = this[0];
      if (typeof c != 'undefined' && c >= 0x80 && c <= 0xef) this[0] = (c & 0xf0) | x;
    }
    return this;
  };
  MIDI.prototype.getNote = function() {
    var c = this[0];
    if (typeof c == 'undefined' || c < 0x80 || c > 0xaf) return;
    return this[1];
  };
  MIDI.prototype.setNote = function(x) {
    var c = this[0];
    if (typeof c == 'undefined' || c < 0x80 || c > 0xaf) return this;
    x = MIDI.noteValue(x);
    if (typeof x != 'undefined') this[1] = x;
    return this;
  };
  MIDI.prototype.getVelocity = function() {
    var c = this[0];
    if (typeof c == 'undefined' || c < 0x80 || c > 0x9f) return;
    return this[2];
  };
  MIDI.prototype.setVelocity = function(x) {
    var c = this[0];
    if (typeof c == 'undefined' || c < 0x80 || c > 0x9f) return this;
    x = parseInt(x);
    if (x >= 0 && x < 128) this[2] = x;
    return this;
  };
  MIDI.prototype.getSysExChannel = function() {
    if (this[0] == 0xf0) return this[2];
  };
  MIDI.prototype.setSysExChannel = function(x) {
    if (this[0] == 0xf0 && this.length > 2) {
      x = parseInt(x);
      if (x >= 0 && x < 128) this[2] = x;
    }
    return this;
  };
  MIDI.prototype.getData = function() {
    if (typeof this.dd != 'undefined') return this.dd.toString();
  };
  MIDI.prototype.setData = function(dd) {
    this.dd = _2s(dd);
    return this;
  };
  MIDI.prototype.getText = function() {
    if (typeof this.dd != 'undefined') return JZZ.lib.fromUTF8(this.dd);
  };
  MIDI.prototype.setText = function(dd) {
    this.dd = JZZ.lib.toUTF8(dd);
    return this;
  };
  MIDI.prototype.getTempo = function() {
    if (this.ff == 0x51 && typeof this.dd != 'undefined') {
      return this.dd.charCodeAt(0) * 65536 + this.dd.charCodeAt(1) * 256 + this.dd.charCodeAt(2);
    }
  };
  MIDI.prototype.getBPM = function() {
    var ms = this.getTempo();
    if (ms) return 60000000 / ms;
  };
  MIDI.prototype.getTimeSignature = function() {
    if (this.ff == 0x58 && typeof this.dd != 'undefined') {
       return [this.dd.charCodeAt(0), 1 << this.dd.charCodeAt(1)];
    }
  };
  MIDI.prototype.getKeySignature = function() {
    if (this.ff == 0x59 && typeof this.dd != 'undefined') {
      var sf = this.dd.charCodeAt(0);
      var mi = this.dd.charCodeAt(1);
      if (sf & 0x80) sf = sf - 0x100;
      if (sf >= -7 && sf <= 7 && mi >= 0 && mi <= 1) {
        return [sf,
          ['Cb', 'Gb', 'Db', 'Ab', 'Eb', 'Bb', 'F', 'C', 'G', 'D', 'A', 'E', 'B', 'F#', 'C#', 'G#', 'D#', 'A#'][mi ? sf + 10 : sf + 7],
          !!mi
        ];
      }
    }
  };

  MIDI.prototype.isNoteOn = function() {
    var c = this[0];
    if (typeof c == 'undefined' || c < 0x90 || c > 0x9f) return false;
    return this[2] > 0 ? true : false;
  };
  MIDI.prototype.isNoteOff = function() {
    var c = this[0];
    if (typeof c == 'undefined' || c < 0x80 || c > 0x9f) return false;
    if (c < 0x90) return true;
    return this[2] == 0 ? true : false;
  };
  MIDI.prototype.isSysEx = function() {
    return this[0] == 0xf0;
  };
  MIDI.prototype.isFullSysEx = function() {
    return this[0] == 0xf0 && this[this.length - 1] == 0xf7;
  };
  MIDI.prototype.isSMF = function() {
    return this.ff >= 0 && this.ff <= 0x7f;
  };
  MIDI.prototype.isEOT = function() {
    return this.ff == 0x2f;
  };
  MIDI.prototype.isTempo = function() {
    return this.ff == 0x51;
  };
  MIDI.prototype.isTimeSignature = function() {
    return this.ff == 0x58;
  };
  MIDI.prototype.isKeySignature = function() {
    return this.ff == 0x59;
  };

  function _s2a(x) {
    var a = [];
    for (var i = 0; i < x.length; i++) {
      a[i] = x.charCodeAt(i);
    }
    return a;
  }
  function _a2s(x) {
    var a = '';
    for (var i = 0; i < x.length; i++) {
      a += String.fromCharCode(x[i]);
    }
    return a;
  }
  function _2s(x) {
    return x instanceof Array ? _a2s(x) : typeof x == 'undefined' ? '' : '' + x;
  }
  function _s2n(x) {
    var n = 0;
    for (var i = 0; i < x.length; i++) n = (n << 8) + x.charCodeAt(i);
    return n;
  }

  function __hex(x) { return (x < 16 ? '0' : '') + x.toString(16); }
  function _hex(x) {
    var a = [];
    for (var i = 0; i < x.length; i++) {
      a[i] = __hex(x[i]);
    }
    return a.join(' ');
  }
  function _toLine(s) {
    var out = '';
    for (var i = 0; i < s.length; i++) {
      if (s[i] == '\n') out += '\\n';
      else if (s[i] == '\r') out += '\\r';
      else if (s[i] == '\t') out += '\\t';
      else if (s.charCodeAt(i) < 32) out += '\\x' + __hex(s.charCodeAt(i));
      else out += s[i];
    }
    return out;
  }
  function _smfhex(dd) {
    return dd.length ? ': ' + _hex(_s2a(dd)) : '';
  }
  function _smftxt(dd) {
    return dd.length ? ': ' + _toLine(JZZ.lib.fromUTF8(dd)) : '';
  }
  MIDI.prototype.toString = function() {
    var s;
    var ss;
    if (!this.length) {
      if (typeof this.ff != 'undefined') {
        s = 'ff' + __hex(this.ff) + ' -- ';
        if (this.ff == 0) s += 'Sequence Number: ' + _s2n(this.dd);
        else if (this.ff > 0 && this.ff < 10) s += ['', 'Text', 'Copyright', 'Sequence Name', 'Instrument Name', 'Lyric', 'Marker', 'Cue Point', 'Program Name', 'Device Name'][this.ff] + _smftxt(this.dd);
        else if (this.ff == 32) s += 'Channel Prefix' + _smfhex(this.dd);
        else if (this.ff == 33) s += 'MIDI Port' + _smfhex(this.dd);
        else if (this.ff == 47) s += 'End of Track' + _smfhex(this.dd);
        else if (this.ff == 81) {
          var bpm = Math.round(this.getBPM() * 100) / 100;
          s += 'Tempo: ' + bpm + ' bpm';
        }
        else if (this.ff == 84) s += 'SMPTE Offset: ' + _smptetxt(_s2a(this.dd));
        else if (this.ff == 88) {
          var d = 1 << this.dd.charCodeAt(1);
          s += 'Time Signature: ' + this.dd.charCodeAt(0) + '/' + d;
          s += ' ' + this.dd.charCodeAt(2) + ' ' + this.dd.charCodeAt(3);
        }
        else if (this.ff == 89) {
          s += 'Key Signature: ';
          var ks = this.getKeySignature();
          if (ks) {
            s += ks[1];
            if (ks[2]) s += ' min';
          }
          else s+= 'invalid';
        }
        else if (this.ff == 127) s += 'Sequencer Specific' + _smfhex(this.dd);
        else s += 'SMF' + _smfhex(this.dd);
        return s;
      }
      return 'empty';
    }
    s = _hex(this);
    if (this[0] < 0x80) return s;
    ss = {
      241: 'MIDI Time Code',
      242: 'Song Position',
      243: 'Song Select',
      244: 'Undefined',
      245: 'Undefined',
      246: 'Tune request',
      248: 'Timing clock',
      249: 'Undefined',
      250: 'Start',
      251: 'Continue',
      252: 'Stop',
      253: 'Undefined',
      254: 'Active Sensing',
      255: 'Reset'
    }[this[0]];
    if (ss) return s + ' -- ' + ss;
    var c = this[0] >> 4;
    ss = {8: 'Note Off', 10: 'Aftertouch', 12: 'Program Change', 13: 'Channel Aftertouch', 14: 'Pitch Wheel'}[c];
    if (ss) return s + ' -- ' + ss;
    if (c == 9) return s + ' -- ' + (this[2] ? 'Note On' : 'Note Off');
    if (c != 11) return s;
    ss = {
      0: 'Bank Select MSB',
      1: 'Modulation Wheel MSB',
      2: 'Breath Controller MSB',
      4: 'Foot Controller MSB',
      5: 'Portamento Time MSB',
      6: 'Data Entry MSB',
      7: 'Channel Volume MSB',
      8: 'Balance MSB',
      10: 'Pan MSB',
      11: 'Expression Controller MSB',
      12: 'Effect Control 1 MSB',
      13: 'Effect Control 2 MSB',
      16: 'General Purpose Controller 1 MSB',
      17: 'General Purpose Controller 2 MSB',
      18: 'General Purpose Controller 3 MSB',
      19: 'General Purpose Controller 4 MSB',
      32: 'Bank Select LSB',
      33: 'Modulation Wheel LSB',
      34: 'Breath Controller LSB',
      36: 'Foot Controller LSB',
      37: 'Portamento Time LSB',
      38: 'Data Entry LSB',
      39: 'Channel Volume LSB',
      40: 'Balance LSB',
      42: 'Pan LSB',
      43: 'Expression Controller LSB',
      44: 'Effect control 1 LSB',
      45: 'Effect control 2 LSB',
      48: 'General Purpose Controller 1 LSB',
      49: 'General Purpose Controller 2 LSB',
      50: 'General Purpose Controller 3 LSB',
      51: 'General Purpose Controller 4 LSB',
      64: 'Damper Pedal On/Off',
      65: 'Portamento On/Off',
      66: 'Sostenuto On/Off',
      67: 'Soft Pedal On/Off',
      68: 'Legato Footswitch',
      69: 'Hold 2',
      70: 'Sound Controller 1',
      71: 'Sound Controller 2',
      72: 'Sound Controller 3',
      73: 'Sound Controller 4',
      74: 'Sound Controller 5',
      75: 'Sound Controller 6',
      76: 'Sound Controller 7',
      77: 'Sound Controller 8',
      78: 'Sound Controller 9',
      79: 'Sound Controller 10',
      80: 'General Purpose Controller 5',
      81: 'General Purpose Controller 6',
      82: 'General Purpose Controller 7',
      83: 'General Purpose Controller 8',
      84: 'Portamento Control',
      88: 'High Resolution Velocity Prefix',
      91: 'Effects 1 Depth',
      92: 'Effects 2 Depth',
      93: 'Effects 3 Depth',
      94: 'Effects 4 Depth',
      95: 'Effects 5 Depth',
      96: 'Data Increment',
      97: 'Data Decrement',
      98: 'Non-Registered Parameter Number LSB',
      99: 'Non-Registered Parameter Number MSB',
      100: 'Registered Parameter Number LSB',
      101: 'Registered Parameter Number MSB',
      120: 'All Sound Off',
      121: 'Reset All Controllers',
      122: 'Local Control On/Off',
      123: 'All Notes Off',
      124: 'Omni Mode Off',
      125: 'Omni Mode On',
      126: 'Mono Mode On',
      127: 'Poly Mode On'
    }[this[1]];
    if (!ss) ss = 'Undefined';
    return s + ' -- ' + ss;
  };
  MIDI.prototype._stamp = function(obj) { this._from.push(obj._orig ? obj._orig : obj); return this; };
  MIDI.prototype._unstamp = function(obj) {
    if (typeof obj == 'undefined') this._from = [];
    else {
      if (obj._orig) obj = obj._orig;
      var i = this._from.indexOf(obj);
      if (i > -1) this._from.splice(i, 1);
    }
    return this;
  };
  MIDI.prototype._stamped = function(obj) {
    if (obj._orig) obj = obj._orig;
    for (var i = 0; i < this._from.length; i++) if (this._from[i] == obj) return true;
    return false;
  };

  JZZ.MIDI = MIDI;

  function MPE() {
    var self = this instanceof MPE ? this : self = new MPE();
    self.reset();
    if (arguments.length) MPE.prototype.setup.apply(self, arguments);
    return self;
  }
  MPE.validate = function(arg) {
    var a = arg instanceof Array ? arg : arguments;
    if (a[0] != parseInt(a[0]) || a[0] < 0 || a[0] > 14) throw RangeError('Bad master channel value: ' + a[0]);
    if (a[1] != parseInt(a[1]) || a[1] < 0 || a[0] + a[1] > 15) throw RangeError('Bad zone size value: ' + a[1]);
  };
  MPE.prototype.reset = function() { for (var n = 0; n < 16; n++) this[n] = { band: 0, master: n }; };
  MPE.prototype.setup = function(m, n) {
    MPE.validate(m, n);
    var k;
    var last = m + n;
    if (this[m].master == m && this[m].band == n) return;
    if (!n && !this[m].band) return;
    if (this[m].band) {
      k = m + this[m].band;
      if (last < k) last = k;
    }
    else if (this[m].master == m - 1) {
      k = m - 1;
      k = k + this[k].band;
      if (last < k) last = k;
      this[m - 1] = { band: 0, master: m - 1 };
    }
    else if (this[m].master != m) {
      k = this[m].master;
      k = k + this[k].band;
      if (last < k) last = k;
      this[this[m].master].band = m - this[m].master - 1;
    }
    this[m].master = m;
    this[m].band = n;
    for (k = m + 1; k <= m + n; k++) {
      if (this[k].band && last < k + this[k].band) last = k + this[k].band;
      this[k] = { band: 0, master: m };
    }
    for (; k <= last; k++) this[k] = { band: 0, master: k };
  };
  MPE.prototype.filter = function(msg) {
    var c = msg.getChannel();
    if (!this[c] || !this[this[c].master].band) return msg;
    var m = this[c].master;
    var n = this[m].band;
    var i, j, k;
    if (typeof msg._mpe != 'undefined') {
      k = 256;
      for (i = m + 1; i <= m + n; i++) {
        if (!this[i].notes) {
          if (k > 0) { c = i; k = 0; }
        }
        else {
          if (k > this[i].notes.length) { c = i; k = this[i].notes.length; }
          for (j = 0; j < this[i].notes.length; j++) {
            if (this[i].notes[j] == msg._mpe) { c = i; k = -1; break; }
          }
        }
      }
      msg.setChannel(c);
      msg._mpe = undefined;
    }
    if (c == m) return msg; // bad mpe
    if (msg.isNoteOn()) {
      if (!this[c].notes) this[c].notes = [];
      _push(this[c].notes, msg.getNote());
    }
    else if (msg.isNoteOff()) {
      if (this[c].notes) _pop(this[c].notes, msg.getNote());
    }
    return msg;
  };
  JZZ.MPE = MPE;

  JZZ.lib = {};
  JZZ.lib.now = _now;
  JZZ.lib.schedule = _schedule;
  JZZ.lib.openMidiOut = function(name, engine) {
    var port = new _M();
    engine._openOut(port);
    port._info = engine._info(name);
    return port;
  };
  JZZ.lib.openMidiIn = function(name, engine) {
    var port = new _M();
    engine._openIn(port);
    port._info = engine._info(name);
    return port;
  };
  JZZ.lib.registerMidiOut = function(name, engine) {
    var x = engine._info(name);
    for (var i = 0; i < _virtual._outs.length; i++) if (_virtual._outs[i].name == x.name) return false;
    x.engine = engine;
    _virtual._outs.push(x);
    if (_jzz) {
      _postRefresh();
      if (_jzz._bad) { _jzz._repair(); _jzz._resume(); }
    }
    return true;
  };
  JZZ.lib.registerMidiIn = function(name, engine) {
    var x = engine._info(name);
    for (var i = 0; i < _virtual._ins.length; i++) if (_virtual._ins[i].name == x.name) return false;
    x.engine = engine;
    _virtual._ins.push(x);
    if (_jzz) {
      _postRefresh();
      if (_jzz._bad) { _jzz._repair(); _jzz._resume(); }
    }
    return true;
  };
  var _ac;
  function _initAudioContext() {
    if (!_ac && typeof window !== 'undefined') {
      var AudioContext = window.AudioContext || window.webkitAudioContext;
      if (AudioContext) {
        _ac = new AudioContext();
        if (_ac && !_ac.createGain) _ac.createGain = _ac.createGainNode;
        var _activateAudioContext = function() {
          if (_ac.state != 'running') {
            _ac.resume();
            var osc = _ac.createOscillator();
            var gain = _ac.createGain();
            try { gain.gain.value = 0; } catch (err) {}
            gain.gain.setTargetAtTime(0, _ac.currentTime, 0.01);
            osc.connect(gain);
            gain.connect(_ac.destination);
            if (!osc.start) osc.start = osc.noteOn;
            if (!osc.stop) osc.stop = osc.noteOff;
            osc.start(0.1); osc.stop(0.11);
          }
          else {
            document.removeEventListener('touchstart', _activateAudioContext);
            document.removeEventListener('touchend', _activateAudioContext);
            document.removeEventListener('mousedown', _activateAudioContext);
            document.removeEventListener('keydown', _activateAudioContext);
          }
        };
        document.addEventListener('touchstart', _activateAudioContext);
        document.addEventListener('touchend', _activateAudioContext);
        document.addEventListener('mousedown', _activateAudioContext);
        document.addEventListener('keydown', _activateAudioContext);
        _activateAudioContext();
      }
    }
  }
  JZZ.lib.copyMidiHelpers = _copyMidiHelpers;
  JZZ.lib.getAudioContext = function() { _initAudioContext(); return _ac; };
  var _b64 = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=';
  JZZ.lib.fromBase64 = function(input) {
    var output = '';
    var chr1, chr2, chr3;
    var enc1, enc2, enc3, enc4;
    var i = 0;
    input = input.replace(/[^A-Za-z0-9+/=]/g, '');
    while (i < input.length) {
      enc1 = _b64.indexOf(input.charAt(i++));
      enc2 = _b64.indexOf(input.charAt(i++));
      enc3 = _b64.indexOf(input.charAt(i++));
      enc4 = _b64.indexOf(input.charAt(i++));
      chr1 = (enc1 << 2) | (enc2 >> 4);
      chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
      chr3 = ((enc3 & 3) << 6) | enc4;
      output = output + String.fromCharCode(chr1);
      if (enc3 != 64) {
        output = output + String.fromCharCode(chr2);
      }
      if (enc4 != 64) {
        output = output + String.fromCharCode(chr3);
      }
    }
    return output;
  };
  JZZ.lib.toBase64 = function(data) {
    var o1, o2, o3, h1, h2, h3, h4, bits, i = 0, ac = 0, enc = '', arr = [];
    if (!data) return data;
    do {
      o1 = data.charCodeAt(i++);
      o2 = data.charCodeAt(i++);
      o3 = data.charCodeAt(i++);
      bits = o1 << 16 | o2 << 8 | o3;
      h1 = bits >> 18 & 0x3f;
      h2 = bits >> 12 & 0x3f;
      h3 = bits >> 6 & 0x3f;
      h4 = bits & 0x3f;
      arr[ac++] = _b64.charAt(h1) + _b64.charAt(h2) + _b64.charAt(h3) + _b64.charAt(h4);
    } while(i < data.length);
    enc = arr.join('');
    var r = data.length % 3;
    return (r ? enc.slice(0, r - 3) + '==='.slice(r) : enc);
  };
  JZZ.lib.fromUTF8 = function(data) {
    data = typeof data == 'undefined' ? '' : '' + data;
    var out = '';
    var i, n, m;
    for (i = 0; i < data.length; i++) {
      n = data.charCodeAt(i);
      if (n > 0xff) return data;
      if (n < 0x80) out += data[i];
      else if ((n & 0xe0) == 0xc0) {
        n = (n & 0x1f) << 6;
        i++; if (i >= data.length) return data;
        m = data.charCodeAt(i);
        if ((m & 0xc0) != 0x80) return data;
        n += (m & 0x3f);
        out += String.fromCharCode(n);
      }
      else if ((n & 0xf0) == 0xe0) {
        n = (n & 0x0f) << 12;
        i++; if (i >= data.length) return data;
        m = data.charCodeAt(i);
        if ((m & 0xc0) != 0x80) return data;
        n += (m & 0x3f) << 6;
        i++; if (i >= data.length) return data;
        m = data.charCodeAt(i);
        if ((m & 0xc0) != 0x80) return data;
        n += (m & 0x3f);
        out += String.fromCharCode(n);
      }
      else if ((n & 0xf8) == 0xf0) {
        n = (n & 0x07) << 18;
        i++; if (i >= data.length) return data;
        m = data.charCodeAt(i);
        if ((m & 0xc0) != 0x80) return data;
        n += (m & 0x3f) << 12;
        i++; if (i >= data.length) return data;
        m = data.charCodeAt(i);
        if ((m & 0xc0) != 0x80) return data;
        n += (m & 0x3f) << 6;
        i++; if (i >= data.length) return data;
        m = data.charCodeAt(i);
        if ((m & 0xc0) != 0x80) return data;
        n += (m & 0x3f);
        if (n > 0x10ffff) return data;
        n -= 0x10000;
        out += String.fromCharCode(0xd800 + (n >> 10));
        out += String.fromCharCode(0xdc00 + (n & 0x3ff));
      }
    }
    return out;
  };
  JZZ.lib.toUTF8 = function(data) {
    data = typeof data == 'undefined' ? '' : '' + data;
    var out = '';
    var i, n;
    for (i = 0; i < data.length; i++) {
      n = data.charCodeAt(i);
      if (n < 0x80) out += data[i];
      else if (n < 0x800) {
        out += String.fromCharCode(0xc0 + (n >> 6));
        out += String.fromCharCode(0x80 + (n & 0x3f));
      }
      else if (n < 0x10000) {
        out += String.fromCharCode(0xe0 + (n >> 12));
        out += String.fromCharCode(0x80 + ((n >> 6) & 0x3f));
        out += String.fromCharCode(0x80 + (n & 0x3f));
      }
      else {
        out += String.fromCharCode(0xf0 + (n >> 18));
        out += String.fromCharCode(0x80 + ((n >> 12) & 0x3f));
        out += String.fromCharCode(0x80 + ((n >> 6) & 0x3f));
        out += String.fromCharCode(0x80 + (n & 0x3f));
      }
    }
    return out;
  };

  // Web MIDI API
  var _wma = [];
  var _outputMap = {};
  var _inputMap = {};

  var Promise = _scope.Promise;
  if (typeof Promise !== 'function') {
    Promise = function(executor) {
      this.executor = executor;
    };
    Promise.prototype.then = function(resolve, reject) {
      if (typeof resolve !== 'function') {
        resolve = function() {};
      }
      if (typeof reject !== 'function') {
        reject = function() {};
      }
      this.executor(resolve, reject);
    };
  }
  function DOMException(name, message, code) {
    this.name = name;
    this.message = message;
    this.code = code;
  }

  function MIDIConnectionEvent(port, target) {
    this.bubbles = false;
    this.cancelBubble = false;
    this.cancelable = false;
    this.currentTarget = target;
    this.defaultPrevented = false;
    this.eventPhase = 0;
    this.path = [];
    this.port = port;
    this.returnValue = true;
    this.srcElement = target;
    this.target = target;
    this.timeStamp = _now();
    this.type = 'statechange';
  }

  function MIDIMessageEvent(port, data) {
    this.bubbles = false;
    this.cancelBubble = false;
    this.cancelable = false;
    this.currentTarget = port;
    this.data = data;
    this.defaultPrevented = false;
    this.eventPhase = 0;
    this.path = [];
    this.receivedTime = _now();
    this.returnValue = true;
    this.srcElement = port;
    this.target = port;
    this.timeStamp = this.receivedTime;
    this.type = 'midimessage';
  }

  function _statechange(p, a) {
    if (p) {
      if (p.onstatechange) p.onstatechange(new MIDIConnectionEvent(p, p));
      if (a.onstatechange) a.onstatechange(new MIDIConnectionEvent(p, a));
    }
  }

  function MIDIInput(a, p) {
    var self = this;
    var _open = false;
    var _ochng = null;
    var _onmsg = null;
    this.type = 'input';
    this.id = p.id;
    this.name = p.name;
    this.manufacturer = p.man;
    this.version = p.ver;
    Object.defineProperty(this, 'state', { get: function() { return p.connected ? 'connected' : 'disconnected'; }, enumerable: true });
    Object.defineProperty(this, 'connection', { get: function() {
      return _open ? p.proxy ? 'open' : 'pending' : 'closed';
    }, enumerable: true });
    Object.defineProperty(this, 'onmidimessage', {
      get: function() { return _onmsg; },
      set: function(value) {
        if (value instanceof Function) {
          _onmsg = value;
          if (!_open) self.open();
        }
        else _onmsg = null;
      },
      enumerable: true
    });
    Object.defineProperty(this, 'onstatechange', {
      get: function() { return _ochng; },
      set: function(value) {
        if (value instanceof Function) _ochng = value;
        else _ochng = null;
      },
      enumerable: true
    });
    this.open = function() {
      return new Promise(function(resolve, reject) {
        if (_open) resolve(self);
        else {
          p.open().then(function() {
            if (!_open) {
              _open = true;
              _statechange(self, a);
            }
            resolve(self);
          }, function() {
            reject(new DOMException('InvalidAccessError', 'Port is not available', 15));
          });
        }
      });
    };
    this.close = function() {
      return new Promise(function(resolve/*, reject*/) {
        if (_open) {
          _open = false;
          p.close();
          _statechange(self, a);
        }
        resolve(self);
      });
    };
    Object.freeze(this);
  }

  function _split(q) {
    var i, k;
    while (q.length) {
      for (i = 0; i < q.length; i++) if (q[i] == parseInt(q[i]) && q[i] >= 0x80 && q[i] <= 0xff && q[i] != 0xf7) break;
      q.splice(0, i);
      if (!q.length) return;
      if (q[0] == 0xf0) {
        for (i = 1; i < q.length; i++) if (q[i] == 0xf7) break;
        if (i == q.length) return;
        return q.splice(0, i + 1);
      }
      else {
        k = _datalen(q[0]) + 1;
        if (k > q.length) return;
        for (i = 1; i < k; i++) if (q[i] != parseInt(q[i]) || q[i] < 0 || q[i] >= 0x80) break;
        if (i == k) return q.splice(0, i);
        else q.splice(0, i);
      }
    }
  }

  function _InputProxy(id, name, man, ver) {
    var self = this;
    this.id = id;
    this.name = name;
    this.man = man;
    this.ver = ver;
    this.connected = true;
    this.ports = [];
    this.pending = [];
    this.proxy = undefined;
    this.queue = [];
    this.onmidi = function(msg) {
      var m;
      self.queue = self.queue.concat(msg.slice());
      for (m = _split(self.queue); m; m = _split(self.queue)) {
        for (i = 0; i < self.ports.length; i++) {
          if (self.ports[i][0].onmidimessage && (m[0] != 0xf0 || self.ports[i][1])) {
            self.ports[i][0].onmidimessage(new MIDIMessageEvent(self, new Uint8Array(m)));
          }
        }
      }
    };
  }
  _InputProxy.prototype.open = function() {
    var self = this;
    return new Promise(function(resolve, reject) {
      var i;
      if (self.proxy || !self.connected) resolve();
      else {
        self.pending.push([resolve, reject]);
        if (self.pending.length == 1) {
          JZZ().openMidiIn(self.name).or(function() {
            for (i = 0; i < self.pending.length; i++) self.pending[i][1]();
            self.pending = [];
          }).and(function() {
            self.proxy = this;
            self.proxy.connect(self.onmidi);
            for (i = 0; i < self.pending.length; i++) self.pending[i][0]();
            self.pending = [];
          });
        }
      }
    });
  };
  _InputProxy.prototype.close = function() {
    var i;
    if (this.proxy) {
      for (i = 0; i < this.ports.length; i++) if (this.ports[i].connection == 'open') return;
      this.proxy.close();
      this.proxy = undefined;
    }
  };
  _InputProxy.prototype.disconnect = function() {
    this.connected = false;
    if (this.proxy) {
      this.proxy.close();
      this.proxy = undefined;
    }
  };
  _InputProxy.prototype.reconnect = function() {
    var self = this;
    var i, p;
    var a = [];
    this.connected = true;
    for (i = 0; i < _wma.length; i++) {
      p = _wma[i].inputs.get(this.id);
      if (p.connection == 'closed') _statechange(p, _wma[i]);
      else a.push([p, _wma[i]]);
    }
    if (a.length) {
      JZZ()._openMidiInNR(self.name).or(function() {
        for (i = 0; i < a.length; i++) a[i][0].close();
      }).and(function() {
        self.proxy = this;
        self.proxy.connect(self.onmidi);
        for (i = 0; i < a.length; i++) _statechange(a[i][0], a[i][1]);
      });
    }
  };

  function _datalen(x) {
    if (x >= 0x80 && x <= 0xbf || x >= 0xe0 && x <= 0xef || x == 0xf2) return 2;
    if (x >= 0xc0 && x <= 0xdf || x == 0xf1 || x == 0xf3) return 1;
    return 0;
  }

  var _epr = "Failed to execute 'send' on 'MIDIOutput': ";

  function _validate(arr, sysex) {
    var i, k;
    var msg;
    var data = [];
    for (i = 0; i < arr.length; i++) {
      if (arr[i] != parseInt(arr[i]) || arr[i] < 0 || arr[i] > 255) throw TypeError(_epr + arr[i] + ' is not a UInt8 value.');
    }
    k = 0;
    for (i = 0; i < arr.length; i++) {
      if (!k) {
        if (arr[i] < 0x80) throw TypeError(_epr + 'Running status is not allowed at index ' + i + ' (' + arr[i] + ').');
        if (arr[i] == 0xf7) throw TypeError(_epr + 'Unexpected end of system exclusive message at index ' + i + ' (' + arr[i] + ').');
        msg = [arr[i]];
        data.push(msg);
        if (arr[i] == 0xf0) {
          if (!sysex) throw new DOMException('InvalidAccessError', _epr + 'System exclusive messag is not allowed at index ' + i + ' (' + arr[i] + ').', 15);
          k = -1;
          for (; i < arr.length; i++) {
            msg.push(arr[i]);
            if (arr[i] == 0xf7) {
              k = 0;
              break;
            }
          }
        }
        else {
          k = _datalen(arr[i]);
        }
      }
      else {
        if (arr[i] > 0x7f) throw TypeError(_epr + 'Unexpected status byte at index ' + i + ' (' + arr[i] + ').');
        msg.push(arr[i]);
        k--;
      }
    }
    if (k) throw TypeError(_epr + 'Message is incomplete');
    return [data];
  }

  function MIDIOutput(a, p) {
    var self = this;
    var _open = false;
    var _ochng = null;
    this.type = 'output';
    this.id = p.id;
    this.name = p.name;
    this.manufacturer = p.man;
    this.version = p.ver;
    Object.defineProperty(this, 'state', { get: function() { return p.connected ? 'connected' : 'disconnected'; }, enumerable: true });
    Object.defineProperty(this, 'connection', { get: function() {
      return _open ? p.proxy ? 'open' : 'pending' : 'closed';
    }, enumerable: true });
    Object.defineProperty(this, 'onstatechange', {
      get: function() { return _ochng; },
      set: function(value) {
        if (value instanceof Function) _ochng = value;
        else _ochng = null;
      },
      enumerable: true
    });
    this.open = function() {
      return new Promise(function(resolve, reject) {
        if (_open) resolve(self);
        else {
          p.open().then(function() {
            if (!_open) {
              _open = true;
              _statechange(self, a);
            }
            resolve(self);
          }, function() {
            reject(new DOMException('InvalidAccessError', 'Port is not available', 15));
          });
        }
      });
    };
    this.close = function() {
      return new Promise(function(resolve/*, reject*/) {
        if (_open) {
          _open = false;
          self.clear();
          p.close();
          _statechange(self, a);
        }
        resolve(self);
      });
    };
    this.clear = function() {
    };
    this.send = function(data, timestamp) {
      _validate(data, a.sysexEnabled);
      if (!p.connected) throw new DOMException('InvalidStateError', 'Port is not connected', 11);
      if (_open) {
        var now = _now();
        if (timestamp > now) setTimeout(function() { p.proxy.send(data); }, timestamp - now);
        else p.proxy.send(data);
      }
      else this.open().then(function() { self.send(data, timestamp); });

    };
    Object.freeze(this);
  }

  function _OutputProxy(id, name, man, ver) {
    this.id = id;
    this.name = name;
    this.man = man;
    this.ver = ver;
    this.connected = true;
    this.ports = [];
    this.pending = [];
    this.proxy = undefined;
  }
  _OutputProxy.prototype.open = function() {
    var self = this;
    return new Promise(function(resolve, reject) {
      var i;
      if (self.proxy || !self.connected) resolve();
      else {
        self.pending.push([resolve, reject]);
        if (self.pending.length == 1) {
          JZZ().openMidiOut(self.name).or(function() {
            for (i = 0; i < self.pending.length; i++) self.pending[i][1]();
            self.pending = [];
          }).and(function() {
            self.proxy = this;
            for (i = 0; i < self.pending.length; i++) self.pending[i][0]();
            self.pending = [];
          });
        }
      }
    });
  };
  _OutputProxy.prototype.close = function() {
    var i;
    if (this.proxy) {
      for (i = 0; i < this.ports.length; i++) if (this.ports[i].connection == 'open') return;
      this.proxy.close();
      this.proxy = undefined;
    }
  };
  _OutputProxy.prototype.disconnect = function() {
    this.connected = false;
    if (this.proxy) {
      this.proxy.close();
      this.proxy = undefined;
    }
  };
  _OutputProxy.prototype.reconnect = function() {
    var self = this;
    var i, p;
    var a = [];
    this.connected = true;
    for (i = 0; i < _wma.length; i++) {
      p = _wma[i].outputs.get(this.id);
      if (p.connection == 'closed') _statechange(p, _wma[i]);
      else a.push([p, _wma[i]]);
    }
    if (a.length) {
      JZZ()._openMidiOutNR(self.name).or(function() {
        for (i = 0; i < a.length; i++) a[i][0].close();
      }).and(function() {
        self.proxy = this;
        for (i = 0; i < a.length; i++) _statechange(a[i][0], a[i][1]);
      });
    }
  };

  function _Maplike(data) {
    this.has = function(id) {
      return data.hasOwnProperty(id) && data[id].connected;
    };
    this.keys = function() {
      try { // some old browsers may have no Map object
        var m = new Map();
        for (var id in data) if (this.has(id)) m.set(id, this.get(id));
        return m.keys();
      } catch (e) {}
    };
    this.values = function() {
      try {
        var m = new Map();
        for (var id in data) if (this.has(id)) m.set(id, this.get(id));
        return m.values();
      } catch (e) {}
    };
    this.entries = function() {
      try {
        var m = new Map();
        for (var id in data) if (this.has(id)) m.set(id, this.get(id));
        return m.entries();
      } catch (e) {}
    };
    this.forEach = function(fun, self) {
      if (typeof self == 'undefined') self = this;
      for (var id in data) if (this.has(id)) fun.call(self, this.get(id), id, this);
    };
    Object.defineProperty(this, 'size', {
      get: function() {
        var len = 0;
        for (var id in data) if (this.has(id)) len++;
        return len;
      },
      enumerable: true
    });
  }

  function MIDIInputMap(_access, _inputs) {
    this.get = function(id) {
      if (_inputMap.hasOwnProperty(id) && _inputMap[id].connected) {
        if (!_inputs[id]) {
          _inputs[id] = new MIDIInput(_access, _inputMap[id]);
          _inputMap[id].ports.push([_inputs[id], _access.sysexEnabled]);
        }
        return _inputs[id];
      }
    };
    Object.freeze(this);
  }
  MIDIInputMap.prototype = new _Maplike(_inputMap);
  MIDIInputMap.prototype.constructor = MIDIInputMap;

  function MIDIOutputMap(_access, _outputs) {
    this.get = function(id) {
      if (_outputMap.hasOwnProperty(id) && _outputMap[id].connected) {
        if (!_outputs[id]) {
          _outputs[id] = new MIDIOutput(_access, _outputMap[id]);
          _outputMap[id].ports.push([_outputs[id], _access.sysexEnabled]);
        }
        return _outputs[id];
      }
    };
    Object.freeze(this);
  }
  MIDIOutputMap.prototype = new _Maplike(_outputMap);
  MIDIOutputMap.prototype.constructor = MIDIOutputMap;

  function _wm_watch(x) {
    var i, k, p, a;
    for (i = 0; i < x.inputs.added.length; i++) {
      p = x.inputs.added[i];
      if (!_inputMap.hasOwnProperty(p.id)) _inputMap[p.id] = new _InputProxy(p.id, p.name, p.manufacturer, p.version);
      _inputMap[p.id].reconnect();
    }
    for (i = 0; i < x.outputs.added.length; i++) {
      p = x.outputs.added[i];
      if (!_outputMap.hasOwnProperty(p.id)) _outputMap[p.id] = new _OutputProxy(p.id, p.name, p.manufacturer, p.version);
      _outputMap[p.id].reconnect();
    }
    for (i = 0; i < x.inputs.removed.length; i++) {
      p = x.inputs.removed[i];
      if (_inputMap.hasOwnProperty(p.id)) {
        a = [];
        for (k = 0; k < _wma.length; k++) a.push([_wma[k].inputs.get(p.id), _wma[k]]);
        _inputMap[p.id].disconnect();
        for (k = 0; k < a.length; k++) _statechange(a[k][0], a[k][1]);
      }
    }
    for (i = 0; i < x.outputs.removed.length; i++) {
      p = x.outputs.removed[i];
      if (_outputMap.hasOwnProperty(p.id)) {
        a = [];
        for (k = 0; k < _wma.length; k++) a.push([_wma[k].outputs.get(p.id), _wma[k]]);
        _outputMap[p.id].disconnect();
        for (k = 0; k < a.length; k++) _statechange(a[k][0], a[k][1]);
      }
    }
  }

  function MIDIAccess(sysex) {
    var _inputs = {};
    var _outputs = {};
    var _onstatechange = null;
    var self = this;
    this.sysexEnabled = sysex;
    this.inputs = new MIDIInputMap(self, _inputs);
    this.outputs = new MIDIOutputMap(self, _outputs);
    Object.defineProperty(this, 'onstatechange', {
      get: function() { return _onstatechange; },
      set: function(f) { _onstatechange = f instanceof Function ? f : null; },
      enumerable: true
    });
    Object.freeze(this);
    var i;
    var p;
    var info = _jzz._info;
    for (i = 0; i < info.inputs.length; i++) {
      p = info.inputs[i];
      if (!_inputMap.hasOwnProperty(p.id)) _inputMap[p.id] = new _InputProxy(p.id, p.name, p.manufacturer, p.version);
    }
    for (i = 0; i < info.outputs.length; i++) {
      p = info.outputs[i];
      if (!_outputMap.hasOwnProperty(p.id)) _outputMap[p.id] = new _OutputProxy(p.id, p.name, p.manufacturer, p.version);
    }
    if (!_wma.length) JZZ().onChange(_wm_watch);
    _wma.push(this);
  }

  JZZ.requestMIDIAccess = function(opt) {
    return new Promise(function(resolve, reject) {
      JZZ.JZZ(opt).or(function() {
      }).and(function() {
        var sysex = !!(opt && opt.sysex);
        if (sysex && !this.info().sysex) reject(new DOMException('SecurityError', 'Sysex is not allowed', 18));
        else {
          var wma = new MIDIAccess(sysex);
          resolve(wma);
        }
      });
    });
  };
  if (typeof navigator !== 'undefined' && !navigator.requestMIDIAccess) navigator.requestMIDIAccess = JZZ.requestMIDIAccess;
  JZZ.close = function() { if (_engine._close) _engine._close(); };

  return JZZ;
})();navigator.requestMIDIAccess = JZZ.requestMIDIAccess;return navigator.requestMIDIAccess();}
/// end: [code injected by Web MIDI API browser extension]

</script><head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta charset="utf-8">
  <link rel="dns-prefetch" href="https://github.githubassets.com/">
  <link rel="dns-prefetch" href="https://avatars0.githubusercontent.com/">
  <link rel="dns-prefetch" href="https://avatars1.githubusercontent.com/">
  <link rel="dns-prefetch" href="https://avatars2.githubusercontent.com/">
  <link rel="dns-prefetch" href="https://avatars3.githubusercontent.com/">
  <link rel="dns-prefetch" href="https://github-cloud.s3.amazonaws.com/">
  <link rel="dns-prefetch" href="https://user-images.githubusercontent.com/">



  <link crossorigin="anonymous" media="all" integrity="sha512-ry2PZfPzRdNeo8l/5UUldzmDbr0q2zsysbKVDDpRiSR92+U0s2BUoJb44bFLp6i6m0VPUklqBQ2wsKWqXs9BeQ==" rel="stylesheet" href="README_files/frameworks-af2d8f65f3f345d35ea3c97fe5452577.css">
  
    <link crossorigin="anonymous" media="all" integrity="sha512-E4RaZABUt6QI+BQsugaaHI9/JcqbHmtsBzzaulGdWE182r5QrqLrHHYx04WCHqc9vwRHYslAhPIHDrQNS9ItiQ==" rel="stylesheet" href="README_files/github-13845a640054b7a408f8142cba069a1c.css">
    
    
    
    

  <script crossorigin="anonymous" defer="defer" integrity="sha512-8K2vvwbW+6H27Nad5ydg8PA2/aMD/LKq+EiK9s0U0hhVZxCI2tWBsYk9beAtisRw2j+Or5k2/F+6dk02nmj/PA==" type="application/javascript" src="README_files/environment-f0adafbf.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-O/NSW+dygCw89FEFysgRjgS45N7cRdVr4XXg2CCslXi5QlxHG7ttTcUx8nSv1YyVkwKciu+vVCuBJCwQ+nmg2A==" type="application/javascript" src="README_files/chunk-frameworks-3bf3525b.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-fifeLCDzeD/nCXw8oPU2CKwv5FZBJPALvJsX89Kh5ENx/lxl+svFDWk0BjvIgtPZGuP6v76INtuILnrurUiNsw==" type="application/javascript" src="README_files/chunk-vendor-7e27de2c.js"></script>
  
  <script crossorigin="anonymous" defer="defer" integrity="sha512-oWYRzt3Wiqs+rO+bUQIyafCNEmEZn2ykIbXvPxnoQ5u+u/GMNApA3tNnp3DjxeJxkhauebYbXxKnBC1kTWP82A==" type="application/javascript" src="README_files/behaviors-a16611ce.js"></script>
  
    <script crossorigin="anonymous" defer="defer" integrity="sha512-F/8sNCLF603gJL0egQeZwFTYP9dfZAVEWHdjMssZ2opLZXRK08vgowBRzKyra6u9zU/rGVxe+igfJsSWzfO2lg==" type="application/javascript" data-module-id="./chunk-contributions-spider-graph.js" data-src="https://github.githubassets.com/assets/chunk-contributions-spider-graph-17ff2c34.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-obMR8mPKx8OvqRe34LgnUcxeJ1qujiA4ND3H6UX13ExMlA/WfHLjEzXRmgGRcRvN/8J1nzc+Z+jgz/PLTFy6zg==" type="application/javascript" data-module-id="./chunk-drag-drop.js" data-src="https://github.githubassets.com/assets/chunk-drag-drop-a1b311f2.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-9zy4ibZe36ye7kOl+7GyJOLVxae8pRSGuTp92DSAI0GJ9ztkgDTGtvfXFHnZ7T3Qh1LRsn2iyn3mJ/Z5Pfo1Fg==" type="application/javascript" data-module-id="./chunk-jump-to.js" data-src="https://github.githubassets.com/assets/chunk-jump-to-f73cb889.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-biWH4OAQPiDiTkaeyDnXf6hHF3u3Mv3eaDEvt8AdT/QvWDpLbnusALT4ZO+f+DgYp07UiHxNRAB6/J7IwPW6TQ==" type="application/javascript" data-module-id="./chunk-lib.dev.js" data-src="https://github.githubassets.com/assets/chunk-lib.dev-6e2587e0.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-tcH4xCRuMBAh1PruDaiwGnRIbHlF6bGLhxyCQ16uqok1cV5QFMguVPWJtN9KI0jGQOgN+Pha3+uOUXhXdfK/qw==" type="application/javascript" data-module-id="./chunk-profile-pins-element.js" data-src="https://github.githubassets.com/assets/chunk-profile-pins-element-b5c1f8c4.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-gPx3bYhTjyC83X5u5KlEDJpwGAHt3AC2p5s9iMuAfPTeSj7kHlKMW231C3K3c7+jvlpWpELk8DJsefrYdRzqjA==" type="application/javascript" data-module-id="./chunk-randomColor.js" data-src="https://github.githubassets.com/assets/chunk-randomColor-80fc776d.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-E+H+wAtjiqutBvn2cnXzDIvmasIhYiS7i7JzOfFUwo+Ej8zT54OrJtP//RhwixnypgOpCF4JvqzYy6zOtORDmg==" type="application/javascript" data-module-id="./chunk-runner-groups.js" data-src="https://github.githubassets.com/assets/chunk-runner-groups-13e1fec0.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-qdiCkJPPR4LxwUKftEmJe2v79E8xnTceYqylsWkMsGuARkiKkX9iFNwkvZJ3bDfS5YHSPD3+k+N2/I73tvlL1Q==" type="application/javascript" data-module-id="./chunk-sortable-behavior.js" data-src="https://github.githubassets.com/assets/chunk-sortable-behavior-a9d88290.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-NpURjBPyJ0JT8hWOMbLErYNeb0bTkKfmFX1hl1F8C/q6jckqWObeOzEAcs6TRlj+cqAR6GDohEBxDgkYBlx+QQ==" type="application/javascript" data-module-id="./chunk-tweetsodium.js" data-src="https://github.githubassets.com/assets/chunk-tweetsodium-3695118c.js"></script>
    <script crossorigin="anonymous" defer="defer" integrity="sha512-/rfwkj1EIni/cASHgs3Z0kyWBjPM3Ge8hYaps5SZwyhFhIP4/MXe5HQ9WYqBY2mwDAli8i1p5lPgfWWCfY7uCQ==" type="application/javascript" data-module-id="./chunk-user-status-submit.js" data-src="https://github.githubassets.com/assets/chunk-user-status-submit-feb7f092.js"></script>
  
  <script crossorigin="anonymous" defer="defer" integrity="sha512-xKAigkDBpzAYKRvYjn2Gdw9qPq5DfGqsCdFr9z5VsCTJ168cuU3Hh91eF/5rzY6V4jrFDImWGyHQGvkpxH6iGQ==" type="application/javascript" src="README_files/codespaces-c4a02282.js"></script>
<script crossorigin="anonymous" defer="defer" integrity="sha512-izbihJx/N9RpfGKX14cTaN33od4II7qxqNmosHTKAphzh1BkhWJlACIdSbxnD2jmYOHSHcbP1Ul3SIqc0Pm24A==" type="application/javascript" src="README_files/repositories-8b36e284.js"></script>
<script crossorigin="anonymous" defer="defer" integrity="sha512-aw5tciVT0IsECUmMuwp9ez60QReE2/yFNL1diLgZnOom6RhU8+0lG3RlAKto4JwbCoEP15E41Pksd7rK5BKfCQ==" type="application/javascript" src="README_files/topic-suggestions-6b0e6d72.js"></script>

  <meta name="viewport" content="width=device-width">
  
  <title>oogre/easy_osc</title>
    <meta name="description" content="Contribute to oogre/easy_osc development by creating an account on GitHub.">
    <link rel="search" type="application/opensearchdescription+xml" href="https://github.com/opensearch.xml" title="GitHub">
  <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub">
  <meta property="fb:app_id" content="1401488693436528">
  <meta name="apple-itunes-app" content="app-id=1477376905">
    <meta name="twitter:image:src" content="https://avatars1.githubusercontent.com/u/2191920?s=400&amp;v=4"><meta name="twitter:site" content="@github"><meta name="twitter:card" content="summary"><meta name="twitter:title" content="oogre/easy_osc"><meta name="twitter:description" content="Contribute to oogre/easy_osc development by creating an account on GitHub.">
    <meta property="og:image" content="https://avatars1.githubusercontent.com/u/2191920?s=400&amp;v=4"><meta property="og:site_name" content="GitHub"><meta property="og:type" content="object"><meta property="og:title" content="oogre/easy_osc"><meta property="og:url" content="https://github.com/oogre/easy_osc"><meta property="og:description" content="Contribute to oogre/easy_osc development by creating an account on GitHub.">



    

  <link rel="assets" href="https://github.githubassets.com/">
    <link rel="shared-web-socket" href="wss://alive.github.com/_sockets/u/2191920/ws?session=eyJ2IjoiVjMiLCJ1IjoyMTkxOTIwLCJzIjo1ODgwMzQ5NTQsImMiOjU2NjM3MTQyOCwidCI6MTYwNzM3ODQ0MX0=--87826ea74a504da650ade588e23e483fa08b4bf3692394089c960d064b025d49" data-refresh-url="/_alive">
  <link rel="sudo-modal" href="https://github.com/sessions/sudo_modal">

  <meta name="request-id" content="E055:5044:5CB796B:82D8BEF:5FCEA609" data-pjax-transient="true"><meta name="html-safe-nonce" content="8f096e8fba8798b3e9e23ba775fed5ae65e453d351400ad0d42d2aecc984ed9f" data-pjax-transient="true"><meta name="visitor-payload" content="eyJyZWZlcnJlciI6Imh0dHBzOi8vZ2l0aHViLmNvbS9uZXciLCJyZXF1ZXN0X2lkIjoiRTA1NTo1MDQ0OjVDQjc5NkI6ODJEOEJFRjo1RkNFQTYwOSIsInZpc2l0b3JfaWQiOiI1ODgyMTYyNjQzNTM2ODQ0MTc0IiwicmVnaW9uX2VkZ2UiOiJmcmEiLCJyZWdpb25fcmVuZGVyIjoiaWFkIn0=" data-pjax-transient="true"><meta name="visitor-hmac" content="466d4fd83b942065415ca448701f79213b902a91a4760bfeca6ef8a444f79de6" data-pjax-transient="true"><meta name="cookie-consent-required" content="true">

    <meta name="hovercard-subject-tag" content="repository:319455446" data-pjax-transient="">


  <meta name="github-keyboard-shortcuts" content="repository" data-pjax-transient="true">

  

  <meta name="selected-link" value="/oogre/easy_osc" data-pjax-transient="">

    <meta name="google-site-verification" content="c1kuD-K2HIVF635lypcsWPoD4kilo5-jA_wBFyT4uMY">
  <meta name="google-site-verification" content="KT5gs8h0wvaagLKAVWq8bbeNwnZZK1r1XQysX3xurLU">
  <meta name="google-site-verification" content="ZzhVyEFwb7w3e0-uOTltm8Jsck2F5StVihD0exw2fsA">
  <meta name="google-site-verification" content="GXs5KoUUkNCoaAZn7wPN-t01Pywp9M3sEjnt_3_ZWPc">

  <meta name="octolytics-host" content="collector.githubapp.com"><meta name="octolytics-app-id" content="github"><meta name="octolytics-event-url" content="https://collector.githubapp.com/github-external/browser_event"><meta name="octolytics-actor-id" content="2191920"><meta name="octolytics-actor-login" content="oogre"><meta name="octolytics-actor-hash" content="ab5a95c7fbf1a36bb64d122350ff5a9c732525ebd9f564de97ddbac946e03952">

  <meta name="analytics-location" content="/&lt;user-name&gt;/&lt;repo-name&gt;/files/disambiguate" data-pjax-transient="true">

  

<meta name="analytics-event" content="Repository, create, target:User; billing:false; repo:public" data-pjax-transient="true">




  

      <meta name="hostname" content="github.com">
    <meta name="user-login" content="oogre">


      <meta name="expected-hostname" content="github.com">

      <meta name="js-proxy-site-detection-payload" content="MjZmMWM4NGVjZDUxYzg5NGFjMzcxOWY0NjliZGI1NTg2NjNmODMyYmVkMjJjYmMyYTgzZWY3MTViNzRmNDhjOHx7InJlbW90ZV9hZGRyZXNzIjoiMTA5LjEzMy4yMzAuOTEiLCJyZXF1ZXN0X2lkIjoiRTA1NTo1MDQ0OjVDQjc5NkI6ODJEOEJFRjo1RkNFQTYwOSIsInRpbWVzdGFtcCI6MTYwNzM3ODQ0MSwiaG9zdCI6ImdpdGh1Yi5jb20ifQ==">

    <meta name="enabled-features" content="MARKETPLACE_PENDING_INSTALLATIONS,JS_HTTP_CACHE_HEADERS">

  <meta http-equiv="x-pjax-version" content="b6394c98b8365f819ae07f50c8267d06ba753fe754465ee380009d4d1cb64d1f">
  

        <link href="https://github.com/oogre/easy_osc/commits/main.atom" rel="alternate" title="Recent Commits to easy_osc:main" type="application/atom+xml">

  <meta name="go-import" content="github.com/oogre/easy_osc git https://github.com/oogre/easy_osc.git">

  <meta name="octolytics-dimension-user_id" content="2191920"><meta name="octolytics-dimension-user_login" content="oogre"><meta name="octolytics-dimension-repository_id" content="319455446"><meta name="octolytics-dimension-repository_nwo" content="oogre/easy_osc"><meta name="octolytics-dimension-repository_public" content="true"><meta name="octolytics-dimension-repository_is_fork" content="false"><meta name="octolytics-dimension-repository_network_root_id" content="319455446"><meta name="octolytics-dimension-repository_network_root_nwo" content="oogre/easy_osc"><meta name="octolytics-dimension-repository_explore_github_marketplace_ci_cta_shown" content="true">





  <meta name="browser-stats-url" content="https://api.github.com/_private/browser/stats">

  <meta name="browser-errors-url" content="https://api.github.com/_private/browser/errors">

  <meta name="browser-optimizely-client-errors-url" content="https://api.github.com/_private/browser/optimizely_client/errors">

  <link rel="mask-icon" href="https://github.githubassets.com/pinned-octocat.svg" color="#000000">
  <link rel="alternate icon" class="js-site-favicon" type="image/png" href="https://github.githubassets.com/favicons/favicon.png">
  <link rel="icon" class="js-site-favicon" type="image/svg+xml" href="https://github.githubassets.com/favicons/favicon.svg">

<meta name="theme-color" content="#1e2327">


  <link rel="manifest" href="https://github.com/manifest.json" crossorigin="use-credentials">

  <meta id="ConnectiveDocSignExtentionInstalled" name="ConnectiveDocSignExtentionInstalled" data-extension-version="1.0.5"></head>

  <body class="logged-in env-production page-responsive">
    

    <div class="position-relative js-header-wrapper ">
      <a href="#start-of-content" class="p-3 bg-blue text-white show-on-focus js-skip-to-content">Skip to content</a>
      <span class="progress-pjax-loader width-full js-pjax-loader-bar Progress position-fixed">
    <span style="background-color: #79b8ff;width: 0%;" class="Progress-item progress-pjax-loader-bar "></span>
</span>      
      


            <header class="Header js-details-container Details px-3 px-md-4 px-lg-5 flex-wrap flex-md-nowrap" role="banner">
    <div class="Header-item mt-n1 mb-n1  d-none d-md-flex">
      <a class="Header-link " href="https://github.com/" data-hotkey="g d" aria-label="Homepage " data-ga-click="Header, go to dashboard, icon:logo">
  <svg class="octicon octicon-mark-github v-align-middle" height="32" viewBox="0 0 16 16" version="1.1" width="32" aria-hidden="true"><path fill-rule="evenodd" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"></path></svg>
</a>

    </div>

    <div class="Header-item d-md-none">
      <button class="Header-link btn-link js-details-target" type="button" aria-label="Toggle navigation" aria-expanded="false">
        <svg height="24" class="octicon octicon-three-bars" viewBox="0 0 16 16" version="1.1" width="24" aria-hidden="true"><path fill-rule="evenodd" d="M1 2.75A.75.75 0 011.75 2h12.5a.75.75 0 110 1.5H1.75A.75.75 0 011 2.75zm0 5A.75.75 0 011.75 7h12.5a.75.75 0 110 1.5H1.75A.75.75 0 011 7.75zM1.75 12a.75.75 0 100 1.5h12.5a.75.75 0 100-1.5H1.75z"></path></svg>
      </button>
    </div>

    <div class="Header-item Header-item--full flex-column flex-md-row width-full flex-order-2 flex-md-order-none mr-0 mr-md-3 mt-3 mt-md-0 Details-content--hidden-not-important d-md-flex">
          <div class="header-search flex-auto js-site-search position-relative flex-self-stretch flex-md-self-auto mb-3 mb-md-0 mr-0 mr-md-3 scoped-search site-scoped-search js-jump-to" role="combobox" aria-owns="jump-to-results" aria-label="Search or jump to" aria-haspopup="listbox" aria-expanded="false">
  <div class="position-relative">
    <!-- '"` --><!-- </textarea></xmp> --><form class="js-site-search-form" role="search" aria-label="Site" data-flagged-in="false" data-scope-type="Repository" data-scope-id="319455446" data-scoped-search-url="/oogre/easy_osc/search" data-owner-scoped-search-url="/users/oogre/search" data-unscoped-search-url="/search" action="/oogre/easy_osc/search" accept-charset="UTF-8" method="get">
      <label class="form-control input-sm header-search-wrapper p-0 js-chromeless-input-container header-search-wrapper-jump-to position-relative d-flex flex-justify-between flex-items-center">
        <input type="text" class="form-control input-sm header-search-input jump-to-field js-jump-to-field js-site-search-focus js-site-search-field is-clearable" data-hotkey="s,/" name="q" placeholder="Search or jump to…" data-unscoped-placeholder="Search or jump to…" data-scoped-placeholder="Search or jump to…" autocapitalize="none" aria-autocomplete="list" aria-controls="jump-to-results" aria-label="Search or jump to…" data-jump-to-suggestions-path="/_graphql/GetSuggestedNavigationDestinations" spellcheck="false" autocomplete="off">
          <input type="hidden" value="D4/RASjcAAlGZOCkAKMLuiToVWKdGMFqDF1beX8LUxm/u/mX8TR0kaLVFHyDXAa70c9SbgeBt0YXRm0PLYY1xA==" data-csrf="true" class="js-data-jump-to-suggestions-path-csrf">
          <input type="hidden" class="js-site-search-type-field" name="type">
            <img src="README_files/search-key-slash.svg" alt="" class="mr-2 header-search-key-slash">

            <div class="Box position-absolute overflow-hidden d-none jump-to-suggestions js-jump-to-suggestions-container">
              
<ul class="d-none js-jump-to-suggestions-template-container">
  

<li class="d-flex flex-justify-start flex-items-center p-0 f5 navigation-item js-navigation-item js-jump-to-suggestion" role="option">
  <a tabindex="-1" class="no-underline d-flex flex-auto flex-items-center jump-to-suggestions-path js-jump-to-suggestion-path js-navigation-open p-2" href="" data-item-type="suggestion">
    <div class="jump-to-octicon js-jump-to-octicon flex-shrink-0 mr-2 text-center d-none">
      <svg height="16" width="16" class="octicon octicon-repo flex-shrink-0 js-jump-to-octicon-repo d-none" title="Repository" aria-label="Repository" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M2 2.5A2.5 2.5 0 014.5 0h8.75a.75.75 0 01.75.75v12.5a.75.75 0 01-.75.75h-2.5a.75.75 0 110-1.5h1.75v-2h-8a1 1 0 00-.714 1.7.75.75 0 01-1.072 1.05A2.495 2.495 0 012 11.5v-9zm10.5-1V9h-8c-.356 0-.694.074-1 .208V2.5a1 1 0 011-1h8zM5 12.25v3.25a.25.25 0 00.4.2l1.45-1.087a.25.25 0 01.3 0L8.6 15.7a.25.25 0 00.4-.2v-3.25a.25.25 0 00-.25-.25h-3.5a.25.25 0 00-.25.25z"></path></svg>
      <svg height="16" width="16" class="octicon octicon-project flex-shrink-0 js-jump-to-octicon-project d-none" title="Project" aria-label="Project" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M1.75 0A1.75 1.75 0 000 1.75v12.5C0 15.216.784 16 1.75 16h12.5A1.75 1.75 0 0016 14.25V1.75A1.75 1.75 0 0014.25 0H1.75zM1.5 1.75a.25.25 0 01.25-.25h12.5a.25.25 0 01.25.25v12.5a.25.25 0 01-.25.25H1.75a.25.25 0 01-.25-.25V1.75zM11.75 3a.75.75 0 00-.75.75v7.5a.75.75 0 001.5 0v-7.5a.75.75 0 00-.75-.75zm-8.25.75a.75.75 0 011.5 0v5.5a.75.75 0 01-1.5 0v-5.5zM8 3a.75.75 0 00-.75.75v3.5a.75.75 0 001.5 0v-3.5A.75.75 0 008 3z"></path></svg>
      <svg height="16" width="16" class="octicon octicon-search flex-shrink-0 js-jump-to-octicon-search d-none" title="Search" aria-label="Search" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M11.5 7a4.499 4.499 0 11-8.998 0A4.499 4.499 0 0111.5 7zm-.82 4.74a6 6 0 111.06-1.06l3.04 3.04a.75.75 0 11-1.06 1.06l-3.04-3.04z"></path></svg>
    </div>

    <img class="avatar mr-2 flex-shrink-0 js-jump-to-suggestion-avatar d-none" alt="" aria-label="Team" src="" width="28" height="28">

    <div class="jump-to-suggestion-name js-jump-to-suggestion-name flex-auto overflow-hidden text-left no-wrap css-truncate css-truncate-target">
    </div>

    <div class="border rounded-1 flex-shrink-0 bg-gray px-1 text-gray-light ml-1 f6 d-none js-jump-to-badge-search">
      <span class="js-jump-to-badge-search-text-default d-none" aria-label="in this repository">
        In this repository
      </span>
      <span class="js-jump-to-badge-search-text-global d-none" aria-label="in all of GitHub">
        All GitHub
      </span>
      <span aria-hidden="true" class="d-inline-block ml-1 v-align-middle">↵</span>
    </div>

    <div aria-hidden="true" class="border rounded-1 flex-shrink-0 bg-gray px-1 text-gray-light ml-1 f6 d-none d-on-nav-focus js-jump-to-badge-jump">
      Jump to
      <span class="d-inline-block ml-1 v-align-middle">↵</span>
    </div>
  </a>
</li>

</ul>

<ul class="d-none js-jump-to-no-results-template-container">
  <li class="d-flex flex-justify-center flex-items-center f5 d-none js-jump-to-suggestion p-2">
    <span class="text-gray">No suggested jump to results</span>
  </li>
</ul>

<ul id="jump-to-results" role="listbox" class="p-0 m-0 js-navigation-container jump-to-suggestions-results-container js-jump-to-suggestions-results-container">
  

<li class="d-flex flex-justify-start flex-items-center p-0 f5 navigation-item js-navigation-item js-jump-to-scoped-search d-none" role="option">
  <a tabindex="-1" class="no-underline d-flex flex-auto flex-items-center jump-to-suggestions-path js-jump-to-suggestion-path js-navigation-open p-2" href="" data-item-type="scoped_search">
    <div class="jump-to-octicon js-jump-to-octicon flex-shrink-0 mr-2 text-center d-none">
      <svg height="16" width="16" class="octicon octicon-repo flex-shrink-0 js-jump-to-octicon-repo d-none" title="Repository" aria-label="Repository" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M2 2.5A2.5 2.5 0 014.5 0h8.75a.75.75 0 01.75.75v12.5a.75.75 0 01-.75.75h-2.5a.75.75 0 110-1.5h1.75v-2h-8a1 1 0 00-.714 1.7.75.75 0 01-1.072 1.05A2.495 2.495 0 012 11.5v-9zm10.5-1V9h-8c-.356 0-.694.074-1 .208V2.5a1 1 0 011-1h8zM5 12.25v3.25a.25.25 0 00.4.2l1.45-1.087a.25.25 0 01.3 0L8.6 15.7a.25.25 0 00.4-.2v-3.25a.25.25 0 00-.25-.25h-3.5a.25.25 0 00-.25.25z"></path></svg>
      <svg height="16" width="16" class="octicon octicon-project flex-shrink-0 js-jump-to-octicon-project d-none" title="Project" aria-label="Project" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M1.75 0A1.75 1.75 0 000 1.75v12.5C0 15.216.784 16 1.75 16h12.5A1.75 1.75 0 0016 14.25V1.75A1.75 1.75 0 0014.25 0H1.75zM1.5 1.75a.25.25 0 01.25-.25h12.5a.25.25 0 01.25.25v12.5a.25.25 0 01-.25.25H1.75a.25.25 0 01-.25-.25V1.75zM11.75 3a.75.75 0 00-.75.75v7.5a.75.75 0 001.5 0v-7.5a.75.75 0 00-.75-.75zm-8.25.75a.75.75 0 011.5 0v5.5a.75.75 0 01-1.5 0v-5.5zM8 3a.75.75 0 00-.75.75v3.5a.75.75 0 001.5 0v-3.5A.75.75 0 008 3z"></path></svg>
      <svg height="16" width="16" class="octicon octicon-search flex-shrink-0 js-jump-to-octicon-search d-none" title="Search" aria-label="Search" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M11.5 7a4.499 4.499 0 11-8.998 0A4.499 4.499 0 0111.5 7zm-.82 4.74a6 6 0 111.06-1.06l3.04 3.04a.75.75 0 11-1.06 1.06l-3.04-3.04z"></path></svg>
    </div>

    <img class="avatar mr-2 flex-shrink-0 js-jump-to-suggestion-avatar d-none" alt="" aria-label="Team" src="" width="28" height="28">

    <div class="jump-to-suggestion-name js-jump-to-suggestion-name flex-auto overflow-hidden text-left no-wrap css-truncate css-truncate-target">
    </div>

    <div class="border rounded-1 flex-shrink-0 bg-gray px-1 text-gray-light ml-1 f6 d-none js-jump-to-badge-search">
      <span class="js-jump-to-badge-search-text-default d-none" aria-label="in this repository">
        In this repository
      </span>
      <span class="js-jump-to-badge-search-text-global d-none" aria-label="in all of GitHub">
        All GitHub
      </span>
      <span aria-hidden="true" class="d-inline-block ml-1 v-align-middle">↵</span>
    </div>

    <div aria-hidden="true" class="border rounded-1 flex-shrink-0 bg-gray px-1 text-gray-light ml-1 f6 d-none d-on-nav-focus js-jump-to-badge-jump">
      Jump to
      <span class="d-inline-block ml-1 v-align-middle">↵</span>
    </div>
  </a>
</li>

  

<li class="d-flex flex-justify-start flex-items-center p-0 f5 navigation-item js-navigation-item js-jump-to-global-search d-none" role="option">
  <a tabindex="-1" class="no-underline d-flex flex-auto flex-items-center jump-to-suggestions-path js-jump-to-suggestion-path js-navigation-open p-2" href="" data-item-type="global_search">
    <div class="jump-to-octicon js-jump-to-octicon flex-shrink-0 mr-2 text-center d-none">
      <svg height="16" width="16" class="octicon octicon-repo flex-shrink-0 js-jump-to-octicon-repo d-none" title="Repository" aria-label="Repository" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M2 2.5A2.5 2.5 0 014.5 0h8.75a.75.75 0 01.75.75v12.5a.75.75 0 01-.75.75h-2.5a.75.75 0 110-1.5h1.75v-2h-8a1 1 0 00-.714 1.7.75.75 0 01-1.072 1.05A2.495 2.495 0 012 11.5v-9zm10.5-1V9h-8c-.356 0-.694.074-1 .208V2.5a1 1 0 011-1h8zM5 12.25v3.25a.25.25 0 00.4.2l1.45-1.087a.25.25 0 01.3 0L8.6 15.7a.25.25 0 00.4-.2v-3.25a.25.25 0 00-.25-.25h-3.5a.25.25 0 00-.25.25z"></path></svg>
      <svg height="16" width="16" class="octicon octicon-project flex-shrink-0 js-jump-to-octicon-project d-none" title="Project" aria-label="Project" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M1.75 0A1.75 1.75 0 000 1.75v12.5C0 15.216.784 16 1.75 16h12.5A1.75 1.75 0 0016 14.25V1.75A1.75 1.75 0 0014.25 0H1.75zM1.5 1.75a.25.25 0 01.25-.25h12.5a.25.25 0 01.25.25v12.5a.25.25 0 01-.25.25H1.75a.25.25 0 01-.25-.25V1.75zM11.75 3a.75.75 0 00-.75.75v7.5a.75.75 0 001.5 0v-7.5a.75.75 0 00-.75-.75zm-8.25.75a.75.75 0 011.5 0v5.5a.75.75 0 01-1.5 0v-5.5zM8 3a.75.75 0 00-.75.75v3.5a.75.75 0 001.5 0v-3.5A.75.75 0 008 3z"></path></svg>
      <svg height="16" width="16" class="octicon octicon-search flex-shrink-0 js-jump-to-octicon-search d-none" title="Search" aria-label="Search" viewBox="0 0 16 16" version="1.1" role="img"><path fill-rule="evenodd" d="M11.5 7a4.499 4.499 0 11-8.998 0A4.499 4.499 0 0111.5 7zm-.82 4.74a6 6 0 111.06-1.06l3.04 3.04a.75.75 0 11-1.06 1.06l-3.04-3.04z"></path></svg>
    </div>

    <img class="avatar mr-2 flex-shrink-0 js-jump-to-suggestion-avatar d-none" alt="" aria-label="Team" src="" width="28" height="28">

    <div class="jump-to-suggestion-name js-jump-to-suggestion-name flex-auto overflow-hidden text-left no-wrap css-truncate css-truncate-target">
    </div>

    <div class="border rounded-1 flex-shrink-0 bg-gray px-1 text-gray-light ml-1 f6 d-none js-jump-to-badge-search">
      <span class="js-jump-to-badge-search-text-default d-none" aria-label="in this repository">
        In this repository
      </span>
      <span class="js-jump-to-badge-search-text-global d-none" aria-label="in all of GitHub">
        All GitHub
      </span>
      <span aria-hidden="true" class="d-inline-block ml-1 v-align-middle">↵</span>
    </div>

    <div aria-hidden="true" class="border rounded-1 flex-shrink-0 bg-gray px-1 text-gray-light ml-1 f6 d-none d-on-nav-focus js-jump-to-badge-jump">
      Jump to
      <span class="d-inline-block ml-1 v-align-middle">↵</span>
    </div>
  </a>
</li>


    <li class="d-flex flex-justify-center flex-items-center p-0 f5 js-jump-to-suggestion">
      <svg viewBox="0 0 16 16" fill="none" style="box-sizing: content-box; color: var(--color-icon-primary);" class="m-3" width="32" height="32">
  <circle cx="8" cy="8" r="7" stroke="currentColor" stroke-opacity="0.25" stroke-width="2" vector-effect="non-scaling-stroke"></circle>
  <path d="M15 8a7.002 7.002 0 00-7-7" stroke="currentColor" stroke-width="2" stroke-linecap="round" vector-effect="non-scaling-stroke">
    <animateTransform attributeName="transform" type="rotate" from="0 8 8" to="360 8 8" dur="1s" repeatCount="indefinite"></animateTransform>
  </path>
</svg>
    </li>
</ul>

            </div>
      </label>
</form>  </div>
</div>

        <nav class="d-flex flex-column flex-md-row flex-self-stretch flex-md-self-auto" aria-label="Global">
      <a class="Header-link py-md-3 d-block d-md-none py-2 border-top border-md-top-0 border-white-fade-15" data-ga-click="Header, click, Nav menu - item:dashboard:user" aria-label="Dashboard" href="https://github.com/dashboard">
        Dashboard
</a>
    <a class="js-selected-navigation-item Header-link mt-md-n3 mb-md-n3 py-2 py-md-3 mr-0 mr-md-3 border-top border-md-top-0 border-white-fade-15" data-hotkey="g p" data-ga-click="Header, click, Nav menu - item:pulls context:user" aria-label="Pull requests you created" data-selected-links="/pulls /pulls/assigned /pulls/mentioned /pulls" href="https://github.com/pulls">
        Pull<span class="d-inline d-md-none d-lg-inline"> request</span>s
</a>
    <a class="js-selected-navigation-item Header-link mt-md-n3 mb-md-n3 py-2 py-md-3 mr-0 mr-md-3 border-top border-md-top-0 border-white-fade-15" data-hotkey="g i" data-ga-click="Header, click, Nav menu - item:issues context:user" aria-label="Issues you created" data-selected-links="/issues /issues/assigned /issues/mentioned /issues" href="https://github.com/issues">
      Issues
</a>

      <div class="d-flex position-relative">
        <a class="js-selected-navigation-item Header-link flex-auto mt-md-n3 mb-md-n3 py-2 py-md-3 mr-0 mr-md-3 border-top border-md-top-0 border-white-fade-15" data-ga-click="Header, click, Nav menu - item:marketplace context:user" data-octo-click="marketplace_click" data-octo-dimensions="location:nav_bar" data-selected-links=" /marketplace" href="https://github.com/marketplace">
          Marketplace
</a>        

      </div>

    <a class="js-selected-navigation-item Header-link mt-md-n3 mb-md-n3 py-2 py-md-3 mr-0 mr-md-3 border-top border-md-top-0 border-white-fade-15" data-ga-click="Header, click, Nav menu - item:explore" data-selected-links="/explore /trending /trending/developers /integrations /integrations/feature/code /integrations/feature/collaborate /integrations/feature/ship showcases showcases_search showcases_landing /explore" href="https://github.com/explore">
      Explore
</a>


    <a class="Header-link d-block d-md-none mr-0 mr-md-3 py-2 py-md-3 border-top border-md-top-0 border-white-fade-15" href="https://github.com/settings/profile">
      Settings
</a>
    <a class="Header-link d-block d-md-none mr-0 mr-md-3 py-2 py-md-3 border-top border-md-top-0 border-white-fade-15" href="https://github.com/oogre">
      <img class="avatar avatar-user" src="README_files/2191920.jpg" alt="@oogre" width="20" height="20">
      oogre
</a>
    <!-- '"` --><!-- </textarea></xmp> --><form action="/logout" accept-charset="UTF-8" method="post"><input type="hidden" name="authenticity_token" value="OPUQUt59DbBxQI1bvoDxuIzJOqii8LGnlNF+LVtEe21lqaX+9qWbgCau08ocLWHaQXNpqAlpvYRxJ+82qos5iQ==">
      <button type="submit" class="Header-link mr-0 mr-md-3 py-2 py-md-3 border-top border-md-top-0 border-white-fade-15 d-md-none btn-link d-block width-full text-left" data-ga-click="Header, sign out, icon:logout" style="padding-left: 2px;">
        <svg class="octicon octicon-sign-out v-align-middle" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M2 2.75C2 1.784 2.784 1 3.75 1h2.5a.75.75 0 010 1.5h-2.5a.25.25 0 00-.25.25v10.5c0 .138.112.25.25.25h2.5a.75.75 0 010 1.5h-2.5A1.75 1.75 0 012 13.25V2.75zm10.44 4.5H6.75a.75.75 0 000 1.5h5.69l-1.97 1.97a.75.75 0 101.06 1.06l3.25-3.25a.75.75 0 000-1.06l-3.25-3.25a.75.75 0 10-1.06 1.06l1.97 1.97z"></path></svg>
        Sign out
      </button>
</form></nav>

    </div>

    <div class="Header-item Header-item--full flex-justify-center d-md-none position-relative">
        <a class="Header-link " href="https://github.com/" data-hotkey="g d" aria-label="Homepage " data-ga-click="Header, go to dashboard, icon:logo">
  <svg class="octicon octicon-mark-github v-align-middle" height="32" viewBox="0 0 16 16" version="1.1" width="32" aria-hidden="true"><path fill-rule="evenodd" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"></path></svg>
</a>

    </div>

    <div class="Header-item mr-0 mr-md-3 flex-order-1 flex-md-order-none">
        

    <notification-indicator class="js-socket-channel" data-channel="eyJjIjoibm90aWZpY2F0aW9uLWNoYW5nZWQ6MjE5MTkyMCIsInQiOjE2MDczNzg0NDF9--f29c8034dff73eb04e1ba9d67d29dcc0099a87a884a11cb5fbbc008a481ee301" data-catalyst="">
      <a href="https://github.com/notifications" class="Header-link notification-indicator position-relative tooltipped tooltipped-sw" aria-label="You have unread notifications" data-hotkey="g n" data-ga-click="Header, go to notifications, icon:unread" data-target="notification-indicator.link">
         <span class="mail-status unread " data-target="notification-indicator.modifier"></span>
         <svg class="octicon octicon-bell" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="M8 16a2 2 0 001.985-1.75c.017-.137-.097-.25-.235-.25h-3.5c-.138 0-.252.113-.235.25A2 2 0 008 16z"></path><path fill-rule="evenodd" d="M8 1.5A3.5 3.5 0 004.5 5v2.947c0 .346-.102.683-.294.97l-1.703 2.556a.018.018 0 00-.003.01l.001.006c0 .002.002.004.004.006a.017.017 0 00.006.004l.007.001h10.964l.007-.001a.016.016 0 00.006-.004.016.016 0 00.004-.006l.001-.007a.017.017 0 00-.003-.01l-1.703-2.554a1.75 1.75 0 01-.294-.97V5A3.5 3.5 0 008 1.5zM3 5a5 5 0 0110 0v2.947c0 .05.015.098.042.139l1.703 2.555A1.518 1.518 0 0113.482 13H2.518a1.518 1.518 0 01-1.263-2.36l1.703-2.554A.25.25 0 003 7.947V5z"></path></svg>
      </a>
    </notification-indicator>

    </div>


    <div class="Header-item position-relative d-none d-md-flex">
        <details class="details-overlay details-reset">
  <summary class="Header-link" aria-label="Create new…" data-ga-click="Header, create new, icon:add" aria-haspopup="menu" role="button">
      <svg class="octicon octicon-plus" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M8 2a.75.75 0 01.75.75v4.5h4.5a.75.75 0 010 1.5h-4.5v4.5a.75.75 0 01-1.5 0v-4.5h-4.5a.75.75 0 010-1.5h4.5v-4.5A.75.75 0 018 2z"></path></svg> <span class="dropdown-caret"></span>
  </summary>
  <details-menu class="dropdown-menu dropdown-menu-sw" role="menu">
    
<a role="menuitem" class="dropdown-item" href="https://github.com/new" data-ga-click="Header, create new repository">
  New repository
</a>

  <a role="menuitem" class="dropdown-item" href="https://github.com/new/import" data-ga-click="Header, import a repository">
    Import repository
  </a>

<a role="menuitem" class="dropdown-item" href="https://gist.github.com/" data-ga-click="Header, create new gist">
  New gist
</a>

  <a role="menuitem" class="dropdown-item" href="https://github.com/organizations/new" data-ga-click="Header, create new organization">
    New organization
  </a>


  <div role="none" class="dropdown-divider"></div>
  <div class="dropdown-header">
    <span title="oogre/easy_osc">This repository</span>
  </div>
    <a role="menuitem" class="dropdown-item" href="https://github.com/oogre/easy_osc/issues/new/choose" data-ga-click="Header, create new issue" data-skip-pjax="">
      New issue
    </a>


  </details-menu>
</details>

    </div>

    <div class="Header-item position-relative mr-0 d-none d-md-flex">
        
  <details class="details-overlay details-reset js-feature-preview-indicator-container" data-feature-preview-indicator-src="/users/oogre/feature_preview/indicator_check">

  <summary class="Header-link" aria-label="View profile and more" data-ga-click="Header, show menu, icon:avatar" aria-haspopup="menu" role="button">
    <img alt="@oogre" src="README_files/2191920_002.jpg" class="avatar avatar-user " width="20" height="20">

      <span class="feature-preview-indicator js-feature-preview-indicator" style="top: 1px;" hidden=""></span>
    <span class="dropdown-caret"></span>
  </summary>
  <details-menu class="dropdown-menu dropdown-menu-sw" style="width: 180px" src="/users/2191920/menu" preload="" role="menu">
      <include-fragment>
        <p class="text-center mt-3" data-hide-on-error="">
          <svg viewBox="0 0 16 16" fill="none" style="box-sizing: content-box; color: var(--color-icon-primary);" width="32" height="32">
  <circle cx="8" cy="8" r="7" stroke="currentColor" stroke-opacity="0.25" stroke-width="2" vector-effect="non-scaling-stroke"></circle>
  <path d="M15 8a7.002 7.002 0 00-7-7" stroke="currentColor" stroke-width="2" stroke-linecap="round" vector-effect="non-scaling-stroke">
    <animateTransform attributeName="transform" type="rotate" from="0 8 8" to="360 8 8" dur="1s" repeatCount="indefinite"></animateTransform>
  </path>
</svg>
        </p>
        <p class="ml-1 mb-2 mt-2 text-gray-dark" data-show-on-error="">
          <svg class="octicon octicon-alert" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M8.22 1.754a.25.25 0 00-.44 0L1.698 13.132a.25.25 0 00.22.368h12.164a.25.25 0 00.22-.368L8.22 1.754zm-1.763-.707c.659-1.234 2.427-1.234 3.086 0l6.082 11.378A1.75 1.75 0 0114.082 15H1.918a1.75 1.75 0 01-1.543-2.575L6.457 1.047zM9 11a1 1 0 11-2 0 1 1 0 012 0zm-.25-5.25a.75.75 0 00-1.5 0v2.5a.75.75 0 001.5 0v-2.5z"></path></svg>
          Sorry, something went wrong.
        </p>
      </include-fragment>
  </details-menu>
</details>

    </div>
</header>

              
    </div>

  <div id="start-of-content" class="show-on-focus"></div>





    <div data-pjax-replace="" id="js-flash-container">


  <template class="js-flash-template">
    <div class="flash flash-full  {{ className }}">
  <div class=" px-2">
    <button class="flash-close js-flash-close" type="button" aria-label="Dismiss this message">
      <svg class="octicon octicon-x" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M3.72 3.72a.75.75 0 011.06 0L8 6.94l3.22-3.22a.75.75 0 111.06 1.06L9.06 8l3.22 3.22a.75.75 0 11-1.06 1.06L8 9.06l-3.22 3.22a.75.75 0 01-1.06-1.06L6.94 8 3.72 4.78a.75.75 0 010-1.06z"></path></svg>
    </button>
    
      <div>{{ message }}</div>

  </div>
</div>
  </template>
</div>


    

  <include-fragment class="js-notification-shelf-include-fragment" data-base-src="https://github.com/notifications/beta/shelf"></include-fragment>




  <div class="application-main " data-commit-hovercards-enabled="" data-discussion-hovercards-enabled="" data-issue-and-pr-hovercards-enabled="">
        <div itemscope="" itemtype="http://schema.org/SoftwareSourceCode" class="">
    <main id="js-repo-pjax-container" data-pjax-container="">
      
    






  


  <div class="bg-gray-light pt-3 hide-full-screen mb-5">

      <div class="d-flex mb-3 px-3 px-md-4 px-lg-5">

        <div class="flex-auto min-width-0 width-fit mr-3">
            <h1 class=" d-flex flex-wrap flex-items-center break-word f3 text-normal">
    <svg class="octicon octicon-repo text-gray mr-2" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M2 2.5A2.5 2.5 0 014.5 0h8.75a.75.75 0 01.75.75v12.5a.75.75 0 01-.75.75h-2.5a.75.75 0 110-1.5h1.75v-2h-8a1 1 0 00-.714 1.7.75.75 0 01-1.072 1.05A2.495 2.495 0 012 11.5v-9zm10.5-1V9h-8c-.356 0-.694.074-1 .208V2.5a1 1 0 011-1h8zM5 12.25v3.25a.25.25 0 00.4.2l1.45-1.087a.25.25 0 01.3 0L8.6 15.7a.25.25 0 00.4-.2v-3.25a.25.25 0 00-.25-.25h-3.5a.25.25 0 00-.25.25z"></path></svg>
    <span class="author flex-self-stretch" itemprop="author">
      <a class="url fn" rel="author" data-hovercard-type="user" data-hovercard-url="/users/oogre/hovercard" data-octo-click="hovercard-link-click" data-octo-dimensions="link_type:self" href="https://github.com/oogre">oogre</a>
    </span>
    <span class="mx-1 flex-self-stretch color-text-secondary">/</span>
  <strong itemprop="name" class="mr-2 flex-self-stretch">
    <a data-pjax="#js-repo-pjax-container" class="" href="https://github.com/oogre/easy_osc">easy_osc</a>
  </strong>
  
</h1>


        </div>

          <ul class="pagehead-actions flex-shrink-0 d-none d-md-inline" style="padding: 2px 0;">

  <li>
          <notifications-list-subscription-form class="f5 position-relative d-flex" data-catalyst="">
      <details class="details-reset details-overlay f5 position-relative" data-target="notifications-list-subscription-form.details" data-action="toggle:notifications-list-subscription-form#detailsToggled">

      <summary class="btn btn-sm rounded-right-0" data-hydro-click="{&quot;event_type&quot;:&quot;repository.click&quot;,&quot;payload&quot;:{&quot;target&quot;:&quot;WATCH_BUTTON&quot;,&quot;repository_id&quot;:319455446,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="1108d06c7b316d2237448ae6c7305368f8fde09ae57698e20bd83ecb6c32f2a8" data-ga-click="Repository, click Watch settings, action:files#disambiguate" aria-label="Notifications settings" role="button" aria-haspopup="menu">
          <span data-menu-button="">
            <span data-target="notifications-list-subscription-form.unwatchButtonCopy">
              <svg class="octicon octicon-eye" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M1.679 7.932c.412-.621 1.242-1.75 2.366-2.717C5.175 4.242 6.527 3.5 8 3.5c1.473 0 2.824.742 3.955 1.715 1.124.967 1.954 2.096 2.366 2.717a.119.119 0 010 .136c-.412.621-1.242 1.75-2.366 2.717C10.825 11.758 9.473 12.5 8 12.5c-1.473 0-2.824-.742-3.955-1.715C2.92 9.818 2.09 8.69 1.679 8.068a.119.119 0 010-.136zM8 2c-1.981 0-3.67.992-4.933 2.078C1.797 5.169.88 6.423.43 7.1a1.619 1.619 0 000 1.798c.45.678 1.367 1.932 2.637 3.024C4.329 13.008 6.019 14 8 14c1.981 0 3.67-.992 4.933-2.078 1.27-1.091 2.187-2.345 2.637-3.023a1.619 1.619 0 000-1.798c-.45-.678-1.367-1.932-2.637-3.023C11.671 2.992 9.981 2 8 2zm0 8a2 2 0 100-4 2 2 0 000 4z"></path></svg>
              Unwatch
            </span>
            <span data-target="notifications-list-subscription-form.stopIgnoringButtonCopy" hidden="">
              <svg class="octicon octicon-bell-slash" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M8 1.5c-.997 0-1.895.416-2.534 1.086A.75.75 0 014.38 1.55 5 5 0 0113 5v2.373a.75.75 0 01-1.5 0V5A3.5 3.5 0 008 1.5zM4.182 4.31L1.19 2.143a.75.75 0 10-.88 1.214L3 5.305v2.642a.25.25 0 01-.042.139L1.255 10.64A1.518 1.518 0 002.518 13h11.108l1.184.857a.75.75 0 10.88-1.214l-1.375-.996a1.196 1.196 0 00-.013-.01L4.198 4.321a.733.733 0 00-.016-.011zm7.373 7.19L4.5 6.391v1.556c0 .346-.102.683-.294.97l-1.703 2.556a.018.018 0 00-.003.01.015.015 0 00.005.012.017.017 0 00.006.004l.007.001h9.037zM8 16a2 2 0 001.985-1.75c.017-.137-.097-.25-.235-.25h-3.5c-.138 0-.252.113-.235.25A2 2 0 008 16z"></path></svg>
              Stop ignoring
            </span>
            <span data-target="notifications-list-subscription-form.watchButtonCopy" hidden="">
              <svg class="octicon octicon-eye" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M1.679 7.932c.412-.621 1.242-1.75 2.366-2.717C5.175 4.242 6.527 3.5 8 3.5c1.473 0 2.824.742 3.955 1.715 1.124.967 1.954 2.096 2.366 2.717a.119.119 0 010 .136c-.412.621-1.242 1.75-2.366 2.717C10.825 11.758 9.473 12.5 8 12.5c-1.473 0-2.824-.742-3.955-1.715C2.92 9.818 2.09 8.69 1.679 8.068a.119.119 0 010-.136zM8 2c-1.981 0-3.67.992-4.933 2.078C1.797 5.169.88 6.423.43 7.1a1.619 1.619 0 000 1.798c.45.678 1.367 1.932 2.637 3.024C4.329 13.008 6.019 14 8 14c1.981 0 3.67-.992 4.933-2.078 1.27-1.091 2.187-2.345 2.637-3.023a1.619 1.619 0 000-1.798c-.45-.678-1.367-1.932-2.637-3.023C11.671 2.992 9.981 2 8 2zm0 8a2 2 0 100-4 2 2 0 000 4z"></path></svg>
              Watch
            </span>
          </span>
          <span class="dropdown-caret"></span>
</summary>
        <details-menu class="SelectMenu  " role="menu" data-target="notifications-list-subscription-form.menu">
          <div class="SelectMenu-modal notifications-component-menu-modal">
            <header class="SelectMenu-header">
              <h3 class="SelectMenu-title">Notifications</h3>
              <button class="SelectMenu-closeButton" type="button" aria-label="Close menu" data-action="click:notifications-list-subscription-form#closeMenu">
                <svg class="octicon octicon-x" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M3.72 3.72a.75.75 0 011.06 0L8 6.94l3.22-3.22a.75.75 0 111.06 1.06L9.06 8l3.22 3.22a.75.75 0 11-1.06 1.06L8 9.06l-3.22 3.22a.75.75 0 01-1.06-1.06L6.94 8 3.72 4.78a.75.75 0 010-1.06z"></path></svg>
              </button>
            </header>

            <div class="SelectMenu-list">
              <form data-target="notifications-list-subscription-form.form" data-action="submit:notifications-list-subscription-form#submitForm" action="/notifications/subscribe" accept-charset="UTF-8" method="post"><input type="hidden" name="authenticity_token" value="WRS9N2bg+8UZwcJEb/c2iF8PKTBDxsIP1dNLAR/LRfDJcS6vX9Oe5H3SWZzKgaKyzE33fXR7Idzrkm1IC1IMkQ==">

                <input type="hidden" name="repository_id" value="319455446">

                <button type="submit" name="do" value="included" class="SelectMenu-item flex-items-start" role="menuitemradio" aria-checked="false" data-targets="notifications-list-subscription-form.subscriptionButtons">
                  <span class="f5">
                    <svg class="octicon octicon-check SelectMenu-icon SelectMenu-icon--check" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M13.78 4.22a.75.75 0 010 1.06l-7.25 7.25a.75.75 0 01-1.06 0L2.22 9.28a.75.75 0 011.06-1.06L6 10.94l6.72-6.72a.75.75 0 011.06 0z"></path></svg>
                  </span>
                  <div>
                    <div class="f5 text-bold">
                      Participating and @mentions
                    </div>
                    <div class="text-small text-gray text-normal pb-1">
                      Only receive notifications from this repo when participating or @mentioned.
                    </div>
                  </div>
                </button>

                <button type="submit" name="do" value="subscribed" class="SelectMenu-item flex-items-start" role="menuitemradio" aria-checked="true" data-targets="notifications-list-subscription-form.subscriptionButtons">
                  <span class="f5">
                    <svg class="octicon octicon-check SelectMenu-icon SelectMenu-icon--check" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M13.78 4.22a.75.75 0 010 1.06l-7.25 7.25a.75.75 0 01-1.06 0L2.22 9.28a.75.75 0 011.06-1.06L6 10.94l6.72-6.72a.75.75 0 011.06 0z"></path></svg>
                  </span>
                  <div>
                    <div class="f5 text-bold">
                      All Activity
                    </div>
                    <div class="text-small text-gray text-normal pb-1">
                      Notified of all notifications on this repo.
                    </div>
                  </div>
                </button>

                <button type="submit" name="do" value="ignore" class="SelectMenu-item flex-items-start" role="menuitemradio" aria-checked="false" data-targets="notifications-list-subscription-form.subscriptionButtons">
                  <span class="f5">
                    <svg class="octicon octicon-check SelectMenu-icon SelectMenu-icon--check" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M13.78 4.22a.75.75 0 010 1.06l-7.25 7.25a.75.75 0 01-1.06 0L2.22 9.28a.75.75 0 011.06-1.06L6 10.94l6.72-6.72a.75.75 0 011.06 0z"></path></svg>
                  </span>
                  <div>
                    <div class="f5 text-bold">
                      Ignore
                    </div>
                    <div class="text-small text-gray text-normal pb-1">
                      Never be notified.
                    </div>
                  </div>
                </button>
</form>
              <button class="SelectMenu-item flex-items-start pr-3" type="button" role="menuitemradio" data-target="notifications-list-subscription-form.customButton" data-action="click:notifications-list-subscription-form#openCustomDialog" aria-haspopup="true" aria-checked="false">
                <span class="f5">
                  <svg class="octicon octicon-check SelectMenu-icon SelectMenu-icon--check" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M13.78 4.22a.75.75 0 010 1.06l-7.25 7.25a.75.75 0 01-1.06 0L2.22 9.28a.75.75 0 011.06-1.06L6 10.94l6.72-6.72a.75.75 0 011.06 0z"></path></svg>
                </span>
                <div>
                  <div class="d-flex flex-items-start flex-justify-between">
                    <div class="f5 text-bold">Custom</div>
                    <div class="f5 pr-1">
                      <svg class="octicon octicon-arrow-right" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M8.22 2.97a.75.75 0 011.06 0l4.25 4.25a.75.75 0 010 1.06l-4.25 4.25a.75.75 0 01-1.06-1.06l2.97-2.97H3.75a.75.75 0 010-1.5h7.44L8.22 4.03a.75.75 0 010-1.06z"></path></svg>
                    </div>
                  </div>
                  <div class="text-small text-gray text-normal pb-1">
                    Select events you want to be notified of in addition to participating and @mentions.
                  </div>
                </div>
              </button>
            </div>
          </div>
        </details-menu>

        <details-dialog class="notifications-component-dialog " data-target="notifications-list-subscription-form.customDialog" role="dialog" aria-modal="true" hidden="">
          <div class="SelectMenu-modal notifications-component-dialog-modal overflow-visible">
            <form data-target="notifications-list-subscription-form.customform" data-action="submit:notifications-list-subscription-form#submitCustomForm" action="/notifications/subscribe" accept-charset="UTF-8" method="post"><input type="hidden" name="authenticity_token" value="bb1deWGHZJTQeGeAQlds9Rc2goudp+0KGrjnFh5cvIn92M7hWLQBtbRr/FjnIfjPhHRcxqoaDtkk+cFfCsX16A==">

              <input type="hidden" name="repository_id" value="319455446">

              <header class="d-sm-none SelectMenu-header pb-0 border-bottom-0 px-2 px-sm-3">
                <h1 class="f3 SelectMenu-title d-inline-flex">
                  <button class="bg-white border-0 px-2 py-0 m-0 link-gray f5" aria-label="Return to menu" type="button" data-action="click:notifications-list-subscription-form#closeCustomDialog">
                    <svg style="" class="octicon octicon-arrow-left" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M7.78 12.53a.75.75 0 01-1.06 0L2.47 8.28a.75.75 0 010-1.06l4.25-4.25a.75.75 0 011.06 1.06L4.81 7h7.44a.75.75 0 010 1.5H4.81l2.97 2.97a.75.75 0 010 1.06z"></path></svg>
                  </button>
                  Custom
                </h1>
              </header>

              <header class="d-none d-sm-flex flex-items-start pt-1">
                <button class="border-0 px-2 pt-1 m-0 link-gray f5" style="background-color: transparent;" aria-label="Return to menu" type="button" data-action="click:notifications-list-subscription-form#closeCustomDialog">
                  <svg style="position: relative; left: 2px; top: 1px" class="octicon octicon-arrow-left" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M7.78 12.53a.75.75 0 01-1.06 0L2.47 8.28a.75.75 0 010-1.06l4.25-4.25a.75.75 0 011.06 1.06L4.81 7h7.44a.75.75 0 010 1.5H4.81l2.97 2.97a.75.75 0 010 1.06z"></path></svg>
                </button>

                <h1 class="pt-1 pr-4 pb-0 pl-0 f5 text-bold">
                  Custom
                </h1>
              </header>

              <fieldset>
                <legend>
                  <div class="text-small text-gray pt-0 pr-3 pb-3 pl-6 pl-sm-5 border-bottom mb-3">
                    Select events you want to be notified of in addition to participating and @mentions.
                  </div>
                </legend>
                  <div class="form-checkbox mr-3 ml-6 ml-sm-5 mb-2 mt-0">
                    <label class="f5 text-normal">
                      <input type="checkbox" name="thread_types[]" value="Issue" data-targets="notifications-list-subscription-form.threadTypeCheckboxes" data-action="change:notifications-list-subscription-form#threadTypeCheckboxesUpdated">
                      Issues
                    </label>

                  </div>
                  <div class="form-checkbox mr-3 ml-6 ml-sm-5 mb-2 mt-0">
                    <label class="f5 text-normal">
                      <input type="checkbox" name="thread_types[]" value="PullRequest" data-targets="notifications-list-subscription-form.threadTypeCheckboxes" data-action="change:notifications-list-subscription-form#threadTypeCheckboxesUpdated">
                      Pull requests
                    </label>

                  </div>
                  <div class="form-checkbox mr-3 ml-6 ml-sm-5 mb-2 mt-0">
                    <label class="f5 text-normal">
                      <input type="checkbox" name="thread_types[]" value="Release" data-targets="notifications-list-subscription-form.threadTypeCheckboxes" data-action="change:notifications-list-subscription-form#threadTypeCheckboxesUpdated">
                      Releases
                    </label>

                  </div>
              </fieldset>
              <div class="pt-2 pb-3 px-3 d-flex flex-justify-start flex-row-reverse">
                <button type="submit" name="do" value="custom" class="btn btn-sm btn-primary ml-2" data-target="notifications-list-subscription-form.customSubmit" disabled="disabled">Apply</button>

                <button class="btn btn-sm" type="button" data-action="click:notifications-list-subscription-form#resetForm" data-close-dialog="">Cancel</button>
              </div>
</form>          </div>
        </details-dialog>
        <div class="notifications-component-dialog-overlay"></div>
      </details>
        <a class="social-count" href="https://github.com/oogre/easy_osc/watchers" aria-label="1 user is watching this repository" data-target="notifications-list-subscription-form.socialCount">
          1
        </a>

    </notifications-list-subscription-form>

  </li>

  <li>
        <div class="d-block js-toggler-container js-social-container starring-container ">
    <form class="starred js-social-form" action="/oogre/easy_osc/unstar" accept-charset="UTF-8" method="post"><input type="hidden" name="authenticity_token" value="+OzsU927+Ugr0PS2RCI/H2e8parqWPFY8Z8bf1LDXchVQ3VKiSg4pP5Rohce7bXPfnWVOL6uqWn6PwswtC8PPw==">
      <input type="hidden" name="context" value="repository">
      <button type="submit" class="btn btn-sm btn-with-count  js-toggler-target" aria-label="Unstar this repository" title="Unstar oogre/easy_osc" data-hydro-click="{&quot;event_type&quot;:&quot;repository.click&quot;,&quot;payload&quot;:{&quot;target&quot;:&quot;UNSTAR_BUTTON&quot;,&quot;repository_id&quot;:319455446,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="17ada95688869a48215079263385c47023a7ae6238b534763196812492f63c03" data-ga-click="Repository, click unstar button, action:files#disambiguate; text:Unstar">        <svg class="octicon octicon-star-fill" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M8 .25a.75.75 0 01.673.418l1.882 3.815 4.21.612a.75.75 0 01.416 1.279l-3.046 2.97.719 4.192a.75.75 0 01-1.088.791L8 12.347l-3.766 1.98a.75.75 0 01-1.088-.79l.72-4.194L.818 6.374a.75.75 0 01.416-1.28l4.21-.611L7.327.668A.75.75 0 018 .25z"></path></svg>
        Unstar
</button>        <a class="social-count js-social-count" href="https://github.com/oogre/easy_osc/stargazers" aria-label="0 users starred this repository">
           0
        </a>
</form>
    <form class="unstarred js-social-form" action="/oogre/easy_osc/star" accept-charset="UTF-8" method="post"><input type="hidden" name="authenticity_token" value="gopBSYlhBfp2FVpI7VWMlcgovR9EyW3ooYLAeQHedE9r+SwALVz9WJDSS6NRXFR+DgQG/o5mTnP/A97U7RtZdg==">
      <input type="hidden" name="context" value="repository">
      <button type="submit" class="btn btn-sm btn-with-count  js-toggler-target" aria-label="Unstar this repository" title="Star oogre/easy_osc" data-hydro-click="{&quot;event_type&quot;:&quot;repository.click&quot;,&quot;payload&quot;:{&quot;target&quot;:&quot;STAR_BUTTON&quot;,&quot;repository_id&quot;:319455446,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="d48f28f60751ee87210b70f8f9bcb8830d1f1027f60cb218845ca3c775542e13" data-ga-click="Repository, click star button, action:files#disambiguate; text:Star">        <svg class="octicon octicon-star" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M8 .25a.75.75 0 01.673.418l1.882 3.815 4.21.612a.75.75 0 01.416 1.279l-3.046 2.97.719 4.192a.75.75 0 01-1.088.791L8 12.347l-3.766 1.98a.75.75 0 01-1.088-.79l.72-4.194L.818 6.374a.75.75 0 01.416-1.28l4.21-.611L7.327.668A.75.75 0 018 .25zm0 2.445L6.615 5.5a.75.75 0 01-.564.41l-3.097.45 2.24 2.184a.75.75 0 01.216.664l-.528 3.084 2.769-1.456a.75.75 0 01.698 0l2.77 1.456-.53-3.084a.75.75 0 01.216-.664l2.24-2.183-3.096-.45a.75.75 0 01-.564-.41L8 2.694v.001z"></path></svg>
        Star
</button>        <a class="social-count js-social-count" href="https://github.com/oogre/easy_osc/stargazers" aria-label="0 users starred this repository">
          0
        </a>
</form>  </div>

  </li>

  <li>
          <span class="btn btn-sm btn-with-count disabled tooltipped tooltipped-sw" aria-label="Cannot fork because repository is empty.">
            <svg class="octicon octicon-repo-forked" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M5 3.25a.75.75 0 11-1.5 0 .75.75 0 011.5 0zm0 2.122a2.25 2.25 0 10-1.5 0v.878A2.25 2.25 0 005.75 8.5h1.5v2.128a2.251 2.251 0 101.5 0V8.5h1.5a2.25 2.25 0 002.25-2.25v-.878a2.25 2.25 0 10-1.5 0v.878a.75.75 0 01-.75.75h-4.5A.75.75 0 015 6.25v-.878zm3.75 7.378a.75.75 0 11-1.5 0 .75.75 0 011.5 0zm3-8.75a.75.75 0 100-1.5.75.75 0 000 1.5z"></path></svg>
            Fork
</span>
      <a href="https://github.com/oogre/easy_osc/network/members" class="social-count" aria-label="0 users forked this repository">
        0
      </a>
  </li>
</ul>

      </div>
        
<nav aria-label="Repository" data-pjax="#js-repo-pjax-container" class="js-repo-nav js-sidenav-container-pjax js-responsive-underlinenav overflow-hidden UnderlineNav px-3 px-md-4 px-lg-5 bg-gray-light">
  <ul class="UnderlineNav-body list-style-none ">
          <li class="d-flex">
        <a class="js-selected-navigation-item selected UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i0code-tab" data-hotkey="g c" data-ga-click="Repository, Navigation click, Code tab" aria-current="page" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches repo_packages repo_deployments /oogre/easy_osc" href="https://github.com/oogre/easy_osc">
              <svg class="octicon octicon-code UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M4.72 3.22a.75.75 0 011.06 1.06L2.06 8l3.72 3.72a.75.75 0 11-1.06 1.06L.47 8.53a.75.75 0 010-1.06l4.25-4.25zm6.56 0a.75.75 0 10-1.06 1.06L13.94 8l-3.72 3.72a.75.75 0 101.06 1.06l4.25-4.25a.75.75 0 000-1.06l-4.25-4.25z"></path></svg>
            <span data-content="Code">Code</span>
              <span title="Not available" class="Counter "></span>
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i1issues-tab" data-hotkey="g i" data-ga-click="Repository, Navigation click, Issues tab" data-selected-links="repo_issues repo_labels repo_milestones /oogre/easy_osc/issues" href="https://github.com/oogre/easy_osc/issues">
              <svg class="octicon octicon-issue-opened UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M8 1.5a6.5 6.5 0 100 13 6.5 6.5 0 000-13zM0 8a8 8 0 1116 0A8 8 0 010 8zm9 3a1 1 0 11-2 0 1 1 0 012 0zm-.25-6.25a.75.75 0 00-1.5 0v3.5a.75.75 0 001.5 0v-3.5z"></path></svg>
            <span data-content="Issues">Issues</span>
              <span title="0" class="Counter " hidden="hidden">0</span>
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i2pull-requests-tab" data-hotkey="g p" data-ga-click="Repository, Navigation click, Pull requests tab" data-selected-links="repo_pulls checks /oogre/easy_osc/pulls" href="https://github.com/oogre/easy_osc/pulls">
              <svg class="octicon octicon-git-pull-request UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M7.177 3.073L9.573.677A.25.25 0 0110 .854v4.792a.25.25 0 01-.427.177L7.177 3.427a.25.25 0 010-.354zM3.75 2.5a.75.75 0 100 1.5.75.75 0 000-1.5zm-2.25.75a2.25 2.25 0 113 2.122v5.256a2.251 2.251 0 11-1.5 0V5.372A2.25 2.25 0 011.5 3.25zM11 2.5h-1V4h1a1 1 0 011 1v5.628a2.251 2.251 0 101.5 0V5A2.5 2.5 0 0011 2.5zm1 10.25a.75.75 0 111.5 0 .75.75 0 01-1.5 0zM3.75 12a.75.75 0 100 1.5.75.75 0 000-1.5z"></path></svg>
            <span data-content="Pull requests">Pull requests</span>
              <span title="0" class="Counter " hidden="hidden">0</span>
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i3actions-tab" data-hotkey="g a" data-ga-click="Repository, Navigation click, Actions tab" data-selected-links="repo_actions /oogre/easy_osc/actions" href="https://github.com/oogre/easy_osc/actions">
              <svg class="octicon octicon-play UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M1.5 8a6.5 6.5 0 1113 0 6.5 6.5 0 01-13 0zM8 0a8 8 0 100 16A8 8 0 008 0zM6.379 5.227A.25.25 0 006 5.442v5.117a.25.25 0 00.379.214l4.264-2.559a.25.25 0 000-.428L6.379 5.227z"></path></svg>
            <span data-content="Actions">Actions</span>
              <span title="Not available" class="Counter "></span>
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i4projects-tab" data-hotkey="g b" data-ga-click="Repository, Navigation click, Projects tab" data-selected-links="repo_projects new_repo_project repo_project /oogre/easy_osc/projects" href="https://github.com/oogre/easy_osc/projects">
              <svg class="octicon octicon-project UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M1.75 0A1.75 1.75 0 000 1.75v12.5C0 15.216.784 16 1.75 16h12.5A1.75 1.75 0 0016 14.25V1.75A1.75 1.75 0 0014.25 0H1.75zM1.5 1.75a.25.25 0 01.25-.25h12.5a.25.25 0 01.25.25v12.5a.25.25 0 01-.25.25H1.75a.25.25 0 01-.25-.25V1.75zM11.75 3a.75.75 0 00-.75.75v7.5a.75.75 0 001.5 0v-7.5a.75.75 0 00-.75-.75zm-8.25.75a.75.75 0 011.5 0v5.5a.75.75 0 01-1.5 0v-5.5zM8 3a.75.75 0 00-.75.75v3.5a.75.75 0 001.5 0v-3.5A.75.75 0 008 3z"></path></svg>
            <span data-content="Projects">Projects</span>
              <span title="0" class="Counter " hidden="hidden">0</span>
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i5wiki-tab" data-hotkey="g w" data-ga-click="Repository, Navigation click, Wikis tab" data-selected-links="repo_wiki /oogre/easy_osc/wiki" href="https://github.com/oogre/easy_osc/wiki">
              <svg class="octicon octicon-book UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M0 1.75A.75.75 0 01.75 1h4.253c1.227 0 2.317.59 3 1.501A3.744 3.744 0 0111.006 1h4.245a.75.75 0 01.75.75v10.5a.75.75 0 01-.75.75h-4.507a2.25 2.25 0 00-1.591.659l-.622.621a.75.75 0 01-1.06 0l-.622-.621A2.25 2.25 0 005.258 13H.75a.75.75 0 01-.75-.75V1.75zm8.755 3a2.25 2.25 0 012.25-2.25H14.5v9h-3.757c-.71 0-1.4.201-1.992.572l.004-7.322zm-1.504 7.324l.004-5.073-.002-2.253A2.25 2.25 0 005.003 2.5H1.5v9h3.757a3.75 3.75 0 011.994.574z"></path></svg>
            <span data-content="Wiki">Wiki</span>
              <span title="Not available" class="Counter "></span>
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i6security-tab" data-hotkey="g s" data-ga-click="Repository, Navigation click, Security tab" data-selected-links="security overview alerts policy token_scanning code_scanning /oogre/easy_osc/security" href="https://github.com/oogre/easy_osc/security">
              <svg class="octicon octicon-shield UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M7.467.133a1.75 1.75 0 011.066 0l5.25 1.68A1.75 1.75 0 0115 3.48V7c0 1.566-.32 3.182-1.303 4.682-.983 1.498-2.585 2.813-5.032 3.855a1.7 1.7 0 01-1.33 0c-2.447-1.042-4.049-2.357-5.032-3.855C1.32 10.182 1 8.566 1 7V3.48a1.75 1.75 0 011.217-1.667l5.25-1.68zm.61 1.429a.25.25 0 00-.153 0l-5.25 1.68a.25.25 0 00-.174.238V7c0 1.358.275 2.666 1.057 3.86.784 1.194 2.121 2.34 4.366 3.297a.2.2 0 00.154 0c2.245-.956 3.582-2.104 4.366-3.298C13.225 9.666 13.5 8.36 13.5 7V3.48a.25.25 0 00-.174-.237l-5.25-1.68zM9 10.5a1 1 0 11-2 0 1 1 0 012 0zm-.25-5.75a.75.75 0 10-1.5 0v3a.75.75 0 001.5 0v-3z"></path></svg>
            <span data-content="Security">Security</span>
              
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i7insights-tab" data-ga-click="Repository, Navigation click, Insights tab" data-selected-links="repo_graphs repo_contributors dependency_graph dependabot_updates pulse people /oogre/easy_osc/pulse" href="https://github.com/oogre/easy_osc/pulse">
              <svg class="octicon octicon-graph UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M1.5 1.75a.75.75 0 00-1.5 0v12.5c0 .414.336.75.75.75h14.5a.75.75 0 000-1.5H1.5V1.75zm14.28 2.53a.75.75 0 00-1.06-1.06L10 7.94 7.53 5.47a.75.75 0 00-1.06 0L3.22 8.72a.75.75 0 001.06 1.06L7 7.06l2.47 2.47a.75.75 0 001.06 0l5.25-5.25z"></path></svg>
            <span data-content="Insights">Insights</span>
              <span title="Not available" class="Counter "></span>
</a>

      </li>
      <li class="d-flex">
        <a class="js-selected-navigation-item UnderlineNav-item hx_underlinenav-item no-wrap js-responsive-underlinenav-item" data-tab-item="i8settings-tab" data-ga-click="Repository, Navigation click, Settings tab" data-selected-links="repo_settings repo_branch_settings hooks integration_installations repo_keys_settings issue_template_editor secrets_settings key_links_settings repo_actions_settings notifications repository_environments /oogre/easy_osc/settings" href="https://github.com/oogre/easy_osc/settings">
              <svg class="octicon octicon-gear UnderlineNav-octicon d-none d-sm-inline" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M7.429 1.525a6.593 6.593 0 011.142 0c.036.003.108.036.137.146l.289 1.105c.147.56.55.967.997 1.189.174.086.341.183.501.29.417.278.97.423 1.53.27l1.102-.303c.11-.03.175.016.195.046.219.31.41.641.573.989.014.031.022.11-.059.19l-.815.806c-.411.406-.562.957-.53 1.456a4.588 4.588 0 010 .582c-.032.499.119 1.05.53 1.456l.815.806c.08.08.073.159.059.19a6.494 6.494 0 01-.573.99c-.02.029-.086.074-.195.045l-1.103-.303c-.559-.153-1.112-.008-1.529.27-.16.107-.327.204-.5.29-.449.222-.851.628-.998 1.189l-.289 1.105c-.029.11-.101.143-.137.146a6.613 6.613 0 01-1.142 0c-.036-.003-.108-.037-.137-.146l-.289-1.105c-.147-.56-.55-.967-.997-1.189a4.502 4.502 0 01-.501-.29c-.417-.278-.97-.423-1.53-.27l-1.102.303c-.11.03-.175-.016-.195-.046a6.492 6.492 0 01-.573-.989c-.014-.031-.022-.11.059-.19l.815-.806c.411-.406.562-.957.53-1.456a4.587 4.587 0 010-.582c.032-.499-.119-1.05-.53-1.456l-.815-.806c-.08-.08-.073-.159-.059-.19a6.44 6.44 0 01.573-.99c.02-.029.086-.075.195-.045l1.103.303c.559.153 1.112.008 1.529-.27.16-.107.327-.204.5-.29.449-.222.851-.628.998-1.189l.289-1.105c.029-.11.101-.143.137-.146zM8 0c-.236 0-.47.01-.701.03-.743.065-1.29.615-1.458 1.261l-.29 1.106c-.017.066-.078.158-.211.224a5.994 5.994 0 00-.668.386c-.123.082-.233.09-.3.071L3.27 2.776c-.644-.177-1.392.02-1.82.63a7.977 7.977 0 00-.704 1.217c-.315.675-.111 1.422.363 1.891l.815.806c.05.048.098.147.088.294a6.084 6.084 0 000 .772c.01.147-.038.246-.088.294l-.815.806c-.474.469-.678 1.216-.363 1.891.2.428.436.835.704 1.218.428.609 1.176.806 1.82.63l1.103-.303c.066-.019.176-.011.299.071.213.143.436.272.668.386.133.066.194.158.212.224l.289 1.106c.169.646.715 1.196 1.458 1.26a8.094 8.094 0 001.402 0c.743-.064 1.29-.614 1.458-1.26l.29-1.106c.017-.066.078-.158.211-.224a5.98 5.98 0 00.668-.386c.123-.082.233-.09.3-.071l1.102.302c.644.177 1.392-.02 1.82-.63.268-.382.505-.789.704-1.217.315-.675.111-1.422-.364-1.891l-.814-.806c-.05-.048-.098-.147-.088-.294a6.1 6.1 0 000-.772c-.01-.147.039-.246.088-.294l.814-.806c.475-.469.679-1.216.364-1.891a7.992 7.992 0 00-.704-1.218c-.428-.609-1.176-.806-1.82-.63l-1.103.303c-.066.019-.176.011-.299-.071a5.991 5.991 0 00-.668-.386c-.133-.066-.194-.158-.212-.224L10.16 1.29C9.99.645 9.444.095 8.701.031A8.094 8.094 0 008 0zm1.5 8a1.5 1.5 0 11-3 0 1.5 1.5 0 013 0zM11 8a3 3 0 11-6 0 3 3 0 016 0z"></path></svg>
            <span data-content="Settings">Settings</span>
              <span title="Not available" class="Counter "></span>
</a>

      </li>

</ul>        <div class="position-absolute right-0 pr-3 pr-md-4 pr-lg-5 js-responsive-underlinenav-overflow" style="visibility:hidden;">
      <details class="details-overlay details-reset position-relative">
  <summary role="button">
    <div class="UnderlineNav-item mr-0 border-0">
            <svg class="octicon octicon-kebab-horizontal" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path d="M8 9a1.5 1.5 0 100-3 1.5 1.5 0 000 3zM1.5 9a1.5 1.5 0 100-3 1.5 1.5 0 000 3zm13 0a1.5 1.5 0 100-3 1.5 1.5 0 000 3z"></path></svg>
            <span class="sr-only">More</span>
          </div>
</summary>  <div>
    <details-menu role="menu" class="dropdown-menu dropdown-menu-sw ">
  
            <ul>
                <li data-menu-item="i0code-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item selected dropdown-item" aria-current="page" data-selected-links=" /oogre/easy_osc" href="https://github.com/oogre/easy_osc">
                    Code
</a>                </li>
                <li data-menu-item="i1issues-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/issues" href="https://github.com/oogre/easy_osc/issues">
                    Issues
</a>                </li>
                <li data-menu-item="i2pull-requests-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/pulls" href="https://github.com/oogre/easy_osc/pulls">
                    Pull requests
</a>                </li>
                <li data-menu-item="i3actions-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/actions" href="https://github.com/oogre/easy_osc/actions">
                    Actions
</a>                </li>
                <li data-menu-item="i4projects-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/projects" href="https://github.com/oogre/easy_osc/projects">
                    Projects
</a>                </li>
                <li data-menu-item="i5wiki-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/wiki" href="https://github.com/oogre/easy_osc/wiki">
                    Wiki
</a>                </li>
                <li data-menu-item="i6security-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/security" href="https://github.com/oogre/easy_osc/security">
                    Security
</a>                </li>
                <li data-menu-item="i7insights-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/pulse" href="https://github.com/oogre/easy_osc/pulse">
                    Insights
</a>                </li>
                <li data-menu-item="i8settings-tab" hidden="">
                  <a role="menuitem" class="js-selected-navigation-item dropdown-item" data-selected-links=" /oogre/easy_osc/settings" href="https://github.com/oogre/easy_osc/settings">
                    Settings
</a>                </li>
            </ul>

</details-menu>
</div></details>    </div>

</nav>
  </div>


<div class="container-xl clearfix new-discussion-timeline px-3 px-md-4 px-lg-5">
  <div class="repository-content ">

    
      


        <git-clone-help class="Box Box--spacious d-block" data-catalyst="">

          <div class="Box-header Box-header--blue">
            <h3><strong>Quick setup</strong> — if you’ve done this kind of thing before</h3>

            <div class="TableObject my-2">
              <div class="TableObject-item">
                <a href="x-github-client://openRepo/https://github.com/oogre/easy_osc" class="btn btn-sm primary js-remove-unless-platform" data-platforms="windows,mac" data-ga-click="Empty repo, click, Clicked Set up in Desktop" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;SET_UP_IN_DESKTOP&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="11f8cc28b995257794998b6b1586087fa14ca45a2c597f524fc3eb384838379c">
                  <svg class="octicon octicon-desktop-download" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M8.75 5V.75a.75.75 0 00-1.5 0V5H5.104a.25.25 0 00-.177.427l2.896 2.896a.25.25 0 00.354 0l2.896-2.896A.25.25 0 0010.896 5H8.75zM1.5 2.75a.25.25 0 01.25-.25h3a.75.75 0 000-1.5h-3A1.75 1.75 0 000 2.75v7.5C0 11.216.784 12 1.75 12h3.727c-.1 1.041-.52 1.872-1.292 2.757A.75.75 0 004.75 16h6.5a.75.75 0 00.565-1.243c-.772-.885-1.193-1.716-1.292-2.757h3.727A1.75 1.75 0 0016 10.25v-7.5A1.75 1.75 0 0014.25 1h-3a.75.75 0 000 1.5h3a.25.25 0 01.25.25v7.5a.25.25 0 01-.25.25H1.75a.25.25 0 01-.25-.25v-7.5zM9.018 12H6.982a5.72 5.72 0 01-.765 2.5h3.566a5.72 5.72 0 01-.765-2.5z"></path></svg> Set up in Desktop
                </a>
              </div>

              <div class="TableObject-item">
                <strong class="mx-3">or</strong>
              </div>

              <div class="TableObject-item">
                <div class="BtnGroup d-flex mr-2">
                      <!-- '"` --><!-- </textarea></xmp> --><form class="BtnGroup-parent" data-remote="true" action="/users/set_protocol?protocol_selector=http&amp;protocol_type=push" accept-charset="UTF-8" method="post"><input type="hidden" name="authenticity_token" value="9ZiTmBnV0Fqgum+rHhGuC2oAiRob4tTFFTrehH/cmWIw59AK6piToxbejMnGEyD6Za9sQ4hLiNndP/55yT2pew==">
                        <button type="submit" class="BtnGroup-item btn btn-sm js-git-protocol-clone-url selected" data-action="click:git-clone-help#updateURL" data-targets="git-clone-help.cloneURLButtons" data-url="https://github.com/oogre/easy_osc.git" data-ga-click="Empty repo, click, Clicked HTTPS protocol" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;COPY_URL_HTTP&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="b5e41d2a4a3dcf59fc42034f1f7c88002415a665a0c8d3d8767f3a2466ffa85a">
                          HTTPS
                        </button>
</form>                      <!-- '"` --><!-- </textarea></xmp> --><form class="BtnGroup-parent" data-remote="true" action="/users/set_protocol?protocol_selector=ssh&amp;protocol_type=push" accept-charset="UTF-8" method="post"><input type="hidden" name="authenticity_token" value="/2SmeK79xHzCgT2Xk6N+2yK2sUOdJprWiQ4HcS9tac46G+XqXbCHhXTl3vVLofAqLRlUGg6PxspBCyeMmYxZ1w==">
                        <button type="submit" class="BtnGroup-item btn btn-sm js-git-protocol-clone-url" data-action="click:git-clone-help#updateURL" data-targets="git-clone-help.cloneURLButtons" data-url="git@github.com:oogre/easy_osc.git" data-ga-click="Empty repo, click, Clicked SSH protocol" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;COPY_URL_SSH&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="a24489debafab727d78f7c1de1e12b9040be1dff14afe59082a0e902afd1e7dd">
                          SSH
                        </button>
</form>                </div>
              </div>

              <div class="TableObject-item TableObject-item--primary">
                <div>
                  <span class="input-group width-full">
                    <input id="empty-setup-clone-url" type="text" readonly="readonly" spellcheck="false" class="form-control input-sm input-monospace" data-target="git-clone-help.helpField" value="https://github.com/oogre/easy_osc.git" aria-label="Clone URL">
                    <span class="input-group-button">
                      <clipboard-copy for="empty-setup-clone-url" aria-label="Copy to clipboard" class="btn btn-sm zeroclipboard-button" data-ga-click="Empty repo, click, Clicked copy URL" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;COPY_URL&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="563bc9aa492e655d2b36f00ff3e6933356241109b53740a925a7adaba3d508c9" tabindex="0" role="button">
                        <svg class="octicon octicon-clippy" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M5.75 1a.75.75 0 00-.75.75v3c0 .414.336.75.75.75h4.5a.75.75 0 00.75-.75v-3a.75.75 0 00-.75-.75h-4.5zm.75 3V2.5h3V4h-3zm-2.874-.467a.75.75 0 00-.752-1.298A1.75 1.75 0 002 3.75v9.5c0 .966.784 1.75 1.75 1.75h8.5A1.75 1.75 0 0014 13.25v-9.5a1.75 1.75 0 00-.874-1.515.75.75 0 10-.752 1.298.25.25 0 01.126.217v9.5a.25.25 0 01-.25.25h-8.5a.25.25 0 01-.25-.25v-9.5a.25.25 0 01.126-.217z"></path></svg>
                      </clipboard-copy>
                    </span>
                  </span>
                </div>
              </div>
            </div>

            <p class="mb-0">
              Get started by
              <a data-ga-click="Empty repo, click, Clicked create new file link" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;CREATING_NEW_FILE&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="e963a95805a79ee5725c7b12de16ace81126a3d0136387564d13a6794843aadd" href="https://github.com/oogre/easy_osc/new/main">creating a new file</a>
              or
              <a data-ga-click="Empty repo, click, Clicked upload file link" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;UPLOADING_EXISTING_FILE&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="7f39927f989d3bd45d3ba271d40ca4cf7aa0c9b8e401f4fbc83fa64f934fdd55" href="https://github.com/oogre/easy_osc/upload">uploading an existing file</a>.

              We recommend every repository include a
              <a data-ga-click="Empty repo, click, Clicked README link" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;README&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="8f36744b7d7430713cbbd345e6c36d0b7808b46211fc0b3f69c69767174d5ecb" href="https://github.com/oogre/easy_osc/new/main?readme=1">README</a>,
              <a data-ga-click="Empty repo, click, Clicked LICENSE link" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;LICENSE&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="5983827108121a14c0a66cf5d708819cc80e99b9e5de45b2e227475a195fb866" href="https://github.com/oogre/easy_osc/new/main?filename=LICENSE.md">LICENSE</a>,
              and <a data-ga-click="Empty repo, click, Clicked .gitignore link" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;GITIGNORE&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="adf5ae74fcf2a3cfa33cabed4b9fc5244e7eddd81e28ab09678a007b94074e3c" href="https://github.com/oogre/easy_osc/new/main?filename=.gitignore">.gitignore</a>.
            </p>
          </div>

          <div><!-- Ensure box rows behave properly -->
            <div class="Box-row">
              <h3>…or create a new repository on the command line</h3>

              <div class="copyable-terminal">
                <div class="copyable-terminal-button">
                  <clipboard-copy for="empty-setup-new-repo-echo" aria-label="Copy to clipboard" class="btn btn-sm zeroclipboard-button" data-ga-click="Empty repo, click, Clicked copy new repo commands" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;COPY_COMMANDS_FOR_CREATING_REPO&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="6770982d050a5d729067fcb621d346de598886154913abee0d11d657519f5fda" tabindex="0" role="button">
                    <svg class="octicon octicon-clippy" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M5.75 1a.75.75 0 00-.75.75v3c0 .414.336.75.75.75h4.5a.75.75 0 00.75-.75v-3a.75.75 0 00-.75-.75h-4.5zm.75 3V2.5h3V4h-3zm-2.874-.467a.75.75 0 00-.752-1.298A1.75 1.75 0 002 3.75v9.5c0 .966.784 1.75 1.75 1.75h8.5A1.75 1.75 0 0014 13.25v-9.5a1.75 1.75 0 00-.874-1.515.75.75 0 10-.752 1.298.25.25 0 01.126.217v9.5a.25.25 0 01-.25.25h-8.5a.25.25 0 01-.25-.25v-9.5a.25.25 0 01.126-.217z"></path></svg>
                  </clipboard-copy>
                </div>
                <pre id="empty-setup-new-repo-echo" class="copyable-terminal-content f5"><span class="user-select-contain">echo "# easy_osc" &gt;&gt; README.md</span>
<span class="user-select-contain">git init</span>
<span class="user-select-contain">git add README.md</span>
<span class="user-select-contain">git commit -m "first commit"</span>
<span class="user-select-contain">git branch -M main</span>
<span class="user-select-contain">git remote add origin <span data-targets="git-clone-help.helpTexts">https://github.com/oogre/easy_osc.git</span></span>
<span class="user-select-contain mb-0">git push -u origin main</span>
                </pre>
              </div>
            </div>

            <div class="Box-row">
              <h3>…or push an existing repository from the command line</h3>

              <div class="copyable-terminal">
                <div class="copyable-terminal-button">
                  <clipboard-copy for="empty-setup-push-repo-echo" aria-label="Copy to clipboard" class="btn btn-sm zeroclipboard-button" data-ga-click="Empty repo, click, Clicked copy existing repo commands" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;COPY_COMMANDS_FOR_UPLOADING_REPO&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="57f6d3944a8a8a2645560835765b0ef7642154a59842e7723ea9a6debb2e864f" tabindex="0" role="button">
                    <svg class="octicon octicon-clippy" height="16" viewBox="0 0 16 16" version="1.1" width="16" aria-hidden="true"><path fill-rule="evenodd" d="M5.75 1a.75.75 0 00-.75.75v3c0 .414.336.75.75.75h4.5a.75.75 0 00.75-.75v-3a.75.75 0 00-.75-.75h-4.5zm.75 3V2.5h3V4h-3zm-2.874-.467a.75.75 0 00-.752-1.298A1.75 1.75 0 002 3.75v9.5c0 .966.784 1.75 1.75 1.75h8.5A1.75 1.75 0 0014 13.25v-9.5a1.75 1.75 0 00-.874-1.515.75.75 0 10-.752 1.298.25.25 0 01.126.217v9.5a.25.25 0 01-.25.25h-8.5a.25.25 0 01-.25-.25v-9.5a.25.25 0 01.126-.217z"></path></svg>
                  </clipboard-copy>
                </div>
                <pre id="empty-setup-push-repo-echo" class="copyable-terminal-content f5"><span class="user-select-contain">git remote add origin <span data-targets="git-clone-help.helpTexts">https://github.com/oogre/easy_osc.git</span></span>
<span class="user-select-contain">git branch -M main</span>
<span class="user-select-contain">git push -u origin main</span></pre>
              </div>
            </div>

            <div class="Box-row">
              <h3>…or import code from another repository</h3>
              <p>You can initialize this repository with code from a Subversion, Mercurial, or TFS project.</p>
              <a href="https://github.com/oogre/easy_osc/import" class="btn btn-sm" data-ga-click="Empty repo, click, Clicked Import code" data-hydro-click="{&quot;event_type&quot;:&quot;repository_empty_state.click&quot;,&quot;payload&quot;:{&quot;event_target&quot;:&quot;IMPORT_CODE&quot;,&quot;repository_context&quot;:&quot;USER&quot;,&quot;originating_url&quot;:&quot;https://github.com/oogre/easy_osc&quot;,&quot;user_id&quot;:2191920}}" data-hydro-click-hmac="f3aa7b34bd00cd8eeb04a11d192c51779e1cb61f668232f7f115f6f88a8c13a9">
                Import code
              </a>
            </div>
          </div>
        </git-clone-help>

        <div class="protip">
          <svg class="octicon octicon-light-bulb text-gray" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M8 1.5c-2.363 0-4 1.69-4 3.75 0 .984.424 1.625.984 2.304l.214.253c.223.264.47.556.673.848.284.411.537.896.621 1.49a.75.75 0 01-1.484.211c-.04-.282-.163-.547-.37-.847a8.695 8.695 0 00-.542-.68c-.084-.1-.173-.205-.268-.32C3.201 7.75 2.5 6.766 2.5 5.25 2.5 2.31 4.863 0 8 0s5.5 2.31 5.5 5.25c0 1.516-.701 2.5-1.328 3.259-.095.115-.184.22-.268.319-.207.245-.383.453-.541.681-.208.3-.33.565-.37.847a.75.75 0 01-1.485-.212c.084-.593.337-1.078.621-1.489.203-.292.45-.584.673-.848.075-.088.147-.173.213-.253.561-.679.985-1.32.985-2.304 0-2.06-1.637-3.75-4-3.75zM6 15.25a.75.75 0 01.75-.75h2.5a.75.75 0 010 1.5h-2.5a.75.75 0 01-.75-.75zM5.75 12a.75.75 0 000 1.5h4.5a.75.75 0 000-1.5h-4.5z"></path></svg>
          <strong>ProTip!</strong> Use the URL for this page when adding GitHub as a remote.
        </div>




  </div>
</div>

    </main>
  </div>

  </div>

          
<div class="footer container-xl width-full p-responsive" role="contentinfo">
    <div class="position-relative d-flex flex-row-reverse flex-lg-row flex-wrap flex-lg-nowrap flex-justify-center flex-lg-justify-between flex-sm-items-center pt-6 pb-2 mt-6 f6 text-gray border-top border-gray-light ">
      <a aria-label="Homepage" title="GitHub" class="footer-octicon d-none d-lg-block mr-lg-4" href="https://github.com/">
        <svg height="24" class="octicon octicon-mark-github" viewBox="0 0 16 16" version="1.1" width="24" aria-hidden="true"><path fill-rule="evenodd" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"></path></svg>
</a>
      <ul class="list-style-none d-flex flex-wrap col-12 flex-justify-center flex-lg-justify-between mb-2 mb-lg-0">
        <li class="mr-3 mr-lg-0">© 2020 GitHub, Inc.</li>
          <li class="mr-3 mr-lg-0"><a data-ga-click="Footer, go to terms, text:terms" href="https://github.com/site/terms">Terms</a></li>
          <li class="mr-3 mr-lg-0"><a data-ga-click="Footer, go to privacy, text:privacy" href="https://github.com/site/privacy">Privacy</a></li>
            <li class="js-cookie-consent-preferences-link-container mr-3 mr-lg-0">
  <button data-ga-click="Footer, go to cookie preferences, text:cookie preferences" class="btn-link js-cookie-consent-preferences-link" type="button">Cookie Preferences</button>
</li>
          <li class="mr-3 mr-lg-0"><a data-ga-click="Footer, go to security, text:security" href="https://github.com/security">Security</a></li>
          <li class="mr-3 mr-lg-0"><a href="https://githubstatus.com/" data-ga-click="Footer, go to status, text:status">Status</a></li>
          <li class="mr-3 mr-lg-0"><a data-ga-click="Footer, go to help, text:help" href="https://docs.github.com/">Help</a></li>
          <li class="mr-3 mr-lg-0"><a data-ga-click="Footer, go to contact, text:contact" href="https://github.com/contact">Contact GitHub</a></li>
          <li class="mr-3 mr-lg-0"><a href="https://github.com/pricing" data-ga-click="Footer, go to Pricing, text:Pricing">Pricing</a></li>
        <li class="mr-3 mr-lg-0"><a href="https://docs.github.com/" data-ga-click="Footer, go to api, text:api">API</a></li>
        <li class="mr-3 mr-lg-0"><a href="https://services.github.com/" data-ga-click="Footer, go to training, text:training">Training</a></li>
          <li class="mr-3 mr-lg-0"><a href="https://github.blog/" data-ga-click="Footer, go to blog, text:blog">Blog</a></li>
          <li class="mr-3 mr-lg-0"><a data-ga-click="Footer, go to about, text:about" href="https://github.com/about">About</a></li>
      </ul>
    </div>
  <div class="d-flex flex-justify-center pb-6">
    <span class="f6 text-gray-light"></span>
  </div>

  
</div>



  <div id="ajax-error-message" class="ajax-error-message flash flash-error">
    <svg class="octicon octicon-alert" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M8.22 1.754a.25.25 0 00-.44 0L1.698 13.132a.25.25 0 00.22.368h12.164a.25.25 0 00.22-.368L8.22 1.754zm-1.763-.707c.659-1.234 2.427-1.234 3.086 0l6.082 11.378A1.75 1.75 0 0114.082 15H1.918a1.75 1.75 0 01-1.543-2.575L6.457 1.047zM9 11a1 1 0 11-2 0 1 1 0 012 0zm-.25-5.25a.75.75 0 00-1.5 0v2.5a.75.75 0 001.5 0v-2.5z"></path></svg>
    <button type="button" class="flash-close js-ajax-error-dismiss" aria-label="Dismiss error">
      <svg class="octicon octicon-x" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M3.72 3.72a.75.75 0 011.06 0L8 6.94l3.22-3.22a.75.75 0 111.06 1.06L9.06 8l3.22 3.22a.75.75 0 11-1.06 1.06L8 9.06l-3.22 3.22a.75.75 0 01-1.06-1.06L6.94 8 3.72 4.78a.75.75 0 010-1.06z"></path></svg>
    </button>
    You can’t perform that action at this time.
  </div>


  <div class="js-stale-session-flash flash flash-warn flash-banner" hidden="">
    <svg class="octicon octicon-alert" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M8.22 1.754a.25.25 0 00-.44 0L1.698 13.132a.25.25 0 00.22.368h12.164a.25.25 0 00.22-.368L8.22 1.754zm-1.763-.707c.659-1.234 2.427-1.234 3.086 0l6.082 11.378A1.75 1.75 0 0114.082 15H1.918a1.75 1.75 0 01-1.543-2.575L6.457 1.047zM9 11a1 1 0 11-2 0 1 1 0 012 0zm-.25-5.25a.75.75 0 00-1.5 0v2.5a.75.75 0 001.5 0v-2.5z"></path></svg>
    <span class="js-stale-session-flash-signed-in" hidden="">You signed in with another tab or window. <a href="">Reload</a> to refresh your session.</span>
    <span class="js-stale-session-flash-signed-out" hidden="">You signed out in another tab or window. <a href="">Reload</a> to refresh your session.</span>
  </div>
    <template id="site-details-dialog">
  <details class="details-reset details-overlay details-overlay-dark lh-default text-gray-dark hx_rsm" open="">
    <summary role="button" aria-label="Close dialog"></summary>
    <details-dialog class="Box Box--overlay d-flex flex-column anim-fade-in fast hx_rsm-dialog hx_rsm-modal">
      <button class="Box-btn-octicon m-0 btn-octicon position-absolute right-0 top-0" type="button" aria-label="Close dialog" data-close-dialog="">
        <svg class="octicon octicon-x" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M3.72 3.72a.75.75 0 011.06 0L8 6.94l3.22-3.22a.75.75 0 111.06 1.06L9.06 8l3.22 3.22a.75.75 0 11-1.06 1.06L8 9.06l-3.22 3.22a.75.75 0 01-1.06-1.06L6.94 8 3.72 4.78a.75.75 0 010-1.06z"></path></svg>
      </button>
      <div class="octocat-spinner my-6 js-details-dialog-spinner"></div>
    </details-dialog>
  </details>
</template>

    <div class="Popover js-hovercard-content position-absolute" style="display: none; outline: none;" tabindex="0">
  <div class="Popover-message Popover-message--bottom-left Popover-message--large Box box-shadow-large" style="width:360px;">
  </div>
</div>

      <div class="js-cookie-consent-banner" hidden="">
  <div class="hx_cookie-banner p-2 p-sm-3 p-md-4">
    <div style="max-width: 1194px;" class="Box hx_cookie-banner-box box-shadow-medium mx-auto">
    <div class="Box-body border-0 py-0 px-3 px-md-4">
      <div class="js-main-cookie-banner hx_cookie-banner-main">
          <div class="d-md-flex flex-items-center py-3">
            <p class="f5 flex-1 mb-3 mb-md-0">
              
  We use <span class="text-bold">optional</span> third-party analytics cookies to understand how you use GitHub.com so we can build better products.

              <span class="btn-link js-cookie-consent-learn-more">Learn more</span>.
            </p>
            <div class="d-flex d-md-block flex-wrap flex-sm-nowrap">
              <button class="btn btn-outline flex-1 mr-1 mx-sm-1 m-md-0 ml-md-2 js-cookie-consent-accept">Accept</button>
              <button class="btn btn-outline flex-1 ml-1 m-md-0 ml-md-2 js-cookie-consent-reject">Reject</button>
            </div>
          </div>
        </div>

        <div class="js-cookie-details hx_cookie-banner-details" hidden="">
          <div class="d-md-flex flex-items-center py-3">
            <p class="f5 flex-1 mb-2 mb-md-0">
              
  We use <span class="text-bold">optional</span> third-party analytics cookies to understand how you use GitHub.com so we can build better products.

              <br>
              You can always update your selection by clicking <span class="text-bold">Cookie Preferences</span> at the bottom of the page.
              For more information, see our <a href="https://docs.github.com/en/free-pro-team@latest/github/site-policy/github-privacy-statement">Privacy Statement</a>.
            </p>
          </div>

          <div class="d-md-flex flex-items-center py-3 border-top">
            <div class="f5 flex-1 mb-2 mb-md-0">
              <h5 class="mb-1">Essential cookies</h5>
              <p class="f6 mb-md-0">We use essential cookies to perform essential website functions, e.g. they're used to log you in. 
                <a href="https://docs.github.com/en/github/site-policy/github-subprocessors-and-cookies">Learn more</a>
              </p>
            </div>
            <div class="text-right">
              <h5 class="text-blue">Always active</h5>
            </div>
          </div>

          <div class="d-md-flex flex-items-center py-3 border-top">
            <div class="f5 flex-1 mb-2 mb-md-0">
              <h5 class="mb-1">Analytics cookies</h5>
              <p class="f6 mb-md-0">We use analytics cookies to 
understand how you use our websites so we can make them better, e.g. 
they're used to gather information about the pages you visit and how 
many clicks you need to accomplish a task. 
                <a href="https://docs.github.com/en/github/site-policy/github-subprocessors-and-cookies">Learn more</a>
              </p>
            </div>
            <div class="text-right">
              <div class="BtnGroup mt-1 mt-md-0 ml-2">
                <button class="btn btn-outline BtnGroup-item js-accept-analytics-cookies" type="button">Accept</button>
                <button class="btn btn-outline BtnGroup-item js-reject-analytics-cookies" type="button">Reject</button>
              </div>
            </div>
          </div>

          <div class="text-right py-3 border-top">
            <button class="btn btn-primary js-save-cookie-preferences" type="button" disabled="disabled">Save preferences</button>
          </div>
        </div>
</div></div>  </div>
</div>


  


<div aria-live="polite" class="sr-only"></div></body></html>