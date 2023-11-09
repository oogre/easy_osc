/*----------------------------------------*\
  receiver_osc - validator.js
  @author Evrard Vincent (vincent@ogre.be)
  @Date:   2023-10-05 21:23:59
  @Last Modified time: 2023-10-05 21:25:58
\*----------------------------------------*/

exports.isInteger = n => Number.isInteger(n);
exports.isFloat = n => n && n % 1 !== 0;
exports.isString = n => n && typeof n == "string";