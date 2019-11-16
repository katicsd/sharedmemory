//shm=require("shm-buffer");
//buffer = shm.open("GW","w",0755,100);

const SM=require('./SharedMemory.js');;
//var b=new Buffer("Hello World!");
//console.log(b.toString());
console.log(SM);
var sp = new SM("Global\\DATCOM_MEM",1700000);
var sa = new SM("Global\\SH_MEM_GW_ANA",80);
var sb = new SM("Global\\SH_MEM_GW_DIG",80);


console.log(sp.open());
console.log(sp.readFloat(1692752));
console.log(sp.writeFloat(1692752,30));
console.log(sp.readFloat(1692752));
/*
console.log(sp.readInt8(1640370));
sp.writeInt8(1640370,0);
console.log(sp.readInt8(1640370));


console.log(sa.open());
console.log(sa.readFloat(0));
console.log(sa.readFloat(4));
console.log(sa.readFloat(8));
console.log(sa.readFloat(12));
console.log(sa.readFloat(16));
console.log(sa.readFloat(20));
console.log(sa.close());

console.log(sb.open());
console.log(sb.readUInt8(54));
console.log(sb.readUInt8(55));
console.log(sb.readUInt8(56));
console.log(sb.readUInt8(57));
console.log(sb.readUInt8(58));
console.log(sb.readUInt8(59));
console.log(sb.close());*/
