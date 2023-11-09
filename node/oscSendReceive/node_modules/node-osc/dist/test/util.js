'use strict';

async function bootstrap(t) {
  const {default: getPorts, portNumbers} = await import('get-port');
  t.context.port = await getPorts({
    port: portNumbers(3000, 3500)
  });
}

exports.bootstrap = bootstrap;
