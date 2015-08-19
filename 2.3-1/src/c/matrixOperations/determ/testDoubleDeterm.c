/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2008 - INRIA - Arnaud TORSET
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */
 
 
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "determ.h"
 
 
 
#define IN2 {0.1998337740078568458557,0.5618660743348300457001,\
0.5896177329123020172119,0.6853979662992060184479f}

#define RES2 -0.1943205386467572182152

#define IN3 {0.8906224733218550682068,0.5042212805710732936859,0.3493615407496690750122,\
0.3873778772540390491486,0.9222898678854107856751,0.9488184261135756969452,\
0.3435337245464324951172,0.3760118731297552585602,0.7340940563008189201355}

#define RES3 0.2464108526639412488635

#define IN4 {0.2615761472843587398529,0.4993493836373090744019,0.2638578419573605060577,\
 0.5253563085570931434631,\
0.5376229803077876567841,0.1199925504624843597412,0.2256303490139544010162,\
 0.6274093082174658775330,\
0.7608432597480714321137,0.0485566202551126480103,0.6723949727602303028107,\
 0.2017172696068882942200,\
0.3911573919467628002167,0.8300316557288169860840,0.5878720157779753208160,\
 0.4829179299995303153992}
 
#define RES4 0.0079215378363537460038

#define IN5 {0.2232865034602582454681,0.8400885667651891708374,0.1205995907075703144074,\
 0.2855364168062806129456,0.8607514644972980022430,\
0.8494101651012897491455,0.5257060811854898929596,0.9931209897622466087341,\
 0.6488562873564660549164,0.9923190940171480178833,\
0.0500419777818024158478,0.7485506581142544746399,0.4104058998636901378632,\
 0.6084526330232620239258,0.8544210889376699924469,\
0.0642646728083491325378,0.8279082938097417354584,0.9262343775480985641480,\
 0.5667211269028484821320,0.5711638936772942543030,\
0.8160110483877360820770,0.0568927936255931854248,0.5595936686731874942780,\
 0.1249340316280722618103,0.7279222286306321620941}
 
#define RES5 0.0501241717143536200108

#define IN6 {0.2677766475826501846314,0.5465334919281303882599,0.9885407658293843269348,\
 0.7395656588487327098846,0.0037173107266426086426,0.5900572859682142734528,\
0.3096467358991503715515,0.2552205710671842098236,0.6251879390329122543335,\
 0.1157417376525700092316,0.6117004090920090675354,0.6783956284634768962860,\
0.3320095278322696685791,0.0258709923364222049713,0.5174468224868178367615,\
 0.3916873238049447536469,0.2413538414984941482544,0.5064434898085892200470,\
0.4236102001741528511047,0.2893727528862655162811,0.0887932181358337402344,\
 0.6212881752289831638336,0.3454984454438090324402,0.7064867629669606685638,\
0.5211472492665052413940,0.2870400850661098957062,0.6502795079723000526428,\
 0.0881334762088954448700,0.4498763345181941986084,0.722725308034569025040,\
0.8976796260103583335877,0.2427821881137788295746,0.4337721113115549087524,\
 0.9677053210325539112091,0.5068534435704350471497,0.523297640960663557053}
 
#define RES6 -0.0275938917848303037761

#define IN8 {0.5596947595477104187012,0.5617307000793516635895,0.468176002614200115204,\
 0.7794546722434461116791,0.7901071812957525253296,0.9808542062528431415558,\
 0.8187066102400422096252,0.4256872381083667278290,\
0.2461560554802417755127,0.922953246627002954483,0.1000745808705687522888,\
 0.4678218117915093898773,0.3950497675687074661255,0.0366117102093994617462,\
 0.5175368534401059150696,0.8325451570563018321991,\
0.6104832142591476440430,0.1871111788786947727203,0.0189574835821986198425,\
 0.8433564766310155391693,0.0748594831675291061401,0.8532815133221447467804,\
 0.0124590108171105384827,0.1867539356462657451630,\
0.4920584075152873992920,0.7489608139730989933014,0.9414957007393240928650,\
 0.212405560072511434555,0.5795019958168268203735,0.2628147569485008716583,\
 0.4360986622050404548645,0.9110545101575553417206,\
0.8082667365670204162598,0.8102653049863874912262,0.2590428395196795463562,\
 0.4139087288640439510346,0.3599927779287099838257,0.6912787933833897113800,\
 0.7656858796253800392151,0.3572649653069674968720,\
0.7693399824202060699463,0.5477633909322321414948,0.0962288742884993553162,\
 0.9561171731911599636078,0.2207408566027879714966,0.0143259358592331409454,\
 0.8191489772871136665344,0.1304992842487990856171,\
0.9682003557682037353516,0.6561381467618048191071,0.2445538965985178947449,\
 0.5283123566769063472748,0.8468925636261701583862,0.7876622085459530353546,\
 0.1262082615867257118225,0.7883860985748469829559,\
0.3453042469918727874756,0.2659857333637773990631,0.9709818651899695396423,\
 0.8875247663818299770355,0.2066752854734659194946,0.8525160965509712696075,\
 0.6744697811082005500794,0.9152874383144080638886}
 
#define RES8 0.1359018266554544440705

#define IN10 {0.0284859761595726013184,0.2367841475643217563629,0.7015343559905886650085,\
 0.1202526628039777278900,0.8287412133067846298218,0.3161072959192097187042,\
 0.5305190766230225563049,0.5715174819342792034149,0.0478015430271625518799,\
 0.8248619721271097660065,\
0.5798843121156096458435,0.2791808298788964748383,0.9545110929757356643677,\
 0.9071154636330902576447,0.3360149310901761054993,0.1175613063387572765350,\
 0.9253723770380020141602,0.7263671257533133029938,0.9009497938677668571472,\
 0.3948993249796330928803,\
0.5655179750174283981323,0.7061489676125347614288,0.6787831196561455726624,\
 0.413293636869639158249,0.1402290873229503631592,0.4952356130816042423248,\
 0.4194877287372946739197,0.8626222289167344570160,0.2857509646564722061157,\
 0.2512136367149651050568,\
0.3389101596549153327942,0.3921975973062217235565,0.4681552127003669738770,\
 0.3361602746881544589996,0.5336876614019274711609,0.2039063959382474422455,\
 0.1589989718049764633179,0.0181815107353031635284,0.4098370606079697608948,\
 0.0105834598653018474579,\
0.1965309716761112213135,0.2725595370866358280182,0.3437655037268996238709,\
 0.2033702037297189235687,0.3011944610625505447388,0.2762595904059708118439,\
 0.2944530742242932319641,0.5718073952011764049530,0.2141770124435424804688,\
 0.6895461627282202243805,\
0.5855572847649455070496,0.4204123034141957759857,0.4277572017163038253784,\
 0.318458587396889925003,0.5761894444003701210022,0.4254902224056422710419,\
 0.9761981628835201263428,0.2518960000015795230866,0.4391129007562994956970,\
 0.075930369552224874496,\
0.2559380177408456802368,0.0670616743154823780060,0.7651131572201848030090,\
 0.0417361590079963207245,0.3438271805644035339356,0.1970167332328855991364,\
 0.2122898651286959648132,0.3140398501418530941010,0.7821625377982854843140,\
 0.0540932347066700458527,\
0.9190206909552216529846,0.4603515709750354290009,0.2992685027420520782471,\
 0.0029166326858103275299,0.8993470584973692893982,0.8387927166186273097992,\
 0.4343749452382326126099,0.7767876130528748035431,0.1395317660644650459290,\
 0.1150637227110564708710,\
0.5355419963598251342773,0.4311733045615255832672,0.614538478665053844452,\
 0.9258962138555943965912,0.0993817280977964401245,0.4280578647740185260773,\
 0.9431830951943993568420,0.0327395270578563213348,0.9213267080485820770264,\
 0.9449024409987032413483,\
0.9007069906219840049744,0.8094316101633012294769,0.0251954291015863418579,\
 0.0019645062275230884552,0.5075221331790089607239,0.4076042952947318553925,\
 0.8408046141266822814941,0.501726570073515176773,0.9128780765458941459656,\
 0.4435729472897946834564}
 
#define RES10 -0.0105698586359502730292




#define ZINR2 {0.9625065480358898639679,0.9798011491075158119202,\
0.0785698364488780498505,0.9150031916797161102295}
#define ZINI2 {0.6172610134817659854889,0.9964194735512137413025,\
0.0468598580919206142426,0.9245926234871149063110}
#define ZRESR2 0.2796908427268796071274
#define ZRESI2 1.3305203939304277582778

#define ZINR3 {0.9689865079708397388458,0.4916289718821644783020,0.2977053108625113964081,\
0.0603054538369178771973,0.631347181741148233414,0.0241030259057879447937,\
0.1527438252232968807221,0.9481177683919668197632,0.2744265575893223285675}
#define ZINI3 {0.4794727200642228126526,0.485576837789267301559,0.676400367170572280884,\
0.8321249918080866336823,0.0125875836238265037537,0.5453779897652566432953,\
0.8426716942340135574341,0.9029165101237595081329,0.4409482078626751899719}
#define ZRESR3 0.3208274162176448784933
#define ZRESI3 -0.5045627162227295237074

#define ZINR4 {0.8332359003834426403046,0.7233976423740386962891,0.4377150186337530612946,\
 0.3080607382580637931824,\
0.8749813153408467769623,0.5355882328003644943237,0.3085998897440731525421,\
 0.3354632416740059852600,\
0.2342486302368342876434,0.2589411698281764984131,0.8521509231068193912506,\
 0.4821739485487341880798,\
0.6095217890106141567230,0.9872822705656290054321,0.9811426815576851367950,\
 0.3303113700821995735169}
#define ZINI4 {0.3589145573787391185761,0.2780527696013450622559,0.9583482020534574985504,\
 0.0156362904235720634460,\
0.2964351712726056575775,0.4685934986919164657593,0.4262020816095173358917,\
 0.4217656338587403297424,\
0.1034853602759540081024,0.4279759414494037628174,0.7860729382373392581940,\
 0.8568082069978117942810,\
0.1993437460623681545258,0.7131301630288362503052,0.5208952468819916248322,\
 0.9311723159626126289368}
#define ZRESR4 0.5916307061533252475982
#define ZRESI4 -0.104762389048400544889

#define ZINR5 {0.4143836158327758312225,0.5980196148157119750977,0.5549105503596365451813,\
 0.8552952585741877555847,0.3097750707529485225678,\
0.9446128141134977340698,0.2442680452950298786163,0.8760446915403008460999,\
 0.4874215493910014629364,0.3844018988311290740967,\
0.0922345430590212345123,0.0705418726429343223572,0.7338807261548936367035,\
 0.7792180571705102920532,0.7827638057060539722443,\
0.2161567779257893562317,0.3420197847299277782440,0.430093832314014434814,\
 0.6261752569116652011871,0.9554250938817858695984,\
0.45415506651625037193,0.0029223021119832992554,0.0106920679099857807159,\
 0.9746370846405625343323,0.7704260940663516521454}
#define ZINI5 {0.6396631337702274322510,0.9535886184312403202057,0.4148483341559767723084,\
 0.4661539695225656032562,0.2238455135375261306763,\
0.3456973326392471790314,0.2340623633936047554016,0.6619341480545699596405,\
 0.2691179513931274414063,0.9830248900689184665680,\
0.7393351225182414054871,0.2902135862968862056732,0.3995949607342481613159,\
 0.9792278115637600421906,0.0075513580814003944397,\
0.7021022657863795757294,0.8907506130635738372803,0.6526974202133715152741,\
 0.4136228552088141441345,0.8581690913997590541840,\
0.2396089676767587661743,0.4820041772909462451935,0.9848585547879338264465,\
 0.4469721647910773754120,0.2329813763499259948731}
#define ZRESR5 -0.2050520846829704535441
#define ZRESI5 1.3442626005968567604043

#define ZINR6 {0.2234513931907713413239,0.8002565456554293632507,0.7750734328292310237885,\
 0.4825006630271673202515,0.7844883133657276630402,0.1534679317846894264221,\
0.7722877110354602336884,0.8952021785080432891846,0.9467325792647898197174,\
 0.6981825744733214378357,0.9559160820208489894867,0.0484017301350831985474,\
0.5323520642705261707306,0.2946867095306515693665,0.6977136689238250255585,\
 0.9376203864812850952148,0.1075560846365988254547,0.7763424394652247428894,\
0.6373417838476598262787,0.0663061570376157760620,0.8169459854252636432648,\
 0.354739100672304630280,0.5860544512979686260223,0.3461025469005107879639,\
0.4424751014448702335358,0.8822665056213736534119,0.7643693066202104091644,\
 0.7764139864593744277954,0.2807680931873619556427,0.6908600600436329841614,\
0.7174728694371879100800,0.372018136084079742432,0.9325496577657759189606,\
 0.2256677551195025444031,0.7521101920865476131439,0.3074750658124685287476}
#define ZINI6 {0.5979326148517429828644,0.1923890346661210060120,0.2387088830582797527313,\
 0.7470833100378513336182,0.9713153676129877567291,0.4370355373248457908630,\
0.6224875054322183132172,0.3291327971965074539185,0.3296387386508285999298,\
 0.2768637137487530708313,0.4872983503155410289764,0.7732046544551849365234,\
0.9077521809376776218414,0.5012293187901377677918,0.5159545852802693843842,\
 0.5792678873986005783081,0.154639363754540681839,0.7611137786880135536194,\
0.6907917778007686138153,0.2873229347169399261475,0.9642531336285173892975,\
 0.5660724332556128501892,0.5782137936912477016449,0.266342097893357276917,\
0.4747098502703011035919,0.6073546530678868293762,0.0409730705432593822479,\
 0.501256845891475677490,0.5295930975116789340973,0.6259458316490054130554,\
0.2219352661632001399994,0.3467419948428869247437,0.3951167692430317401886,\
 0.5442812526598572731018,0.1430782820098102092743,0.7165467627346515655518}
#define ZRESR6 0.0374364367907719236550
#define ZRESI6 0.0027318151340892903034

#define ZINR8 {0.826897530350834131241,0.0803818320855498313904,0.7634756616316735744476,\
 0.6771226990967988967896,0.0800866526551544666290,0.5631617354229092597961,\
 0.8400143641047179698944,0.9142984896898269653320,\
0.9566112258471548557282,0.1676578698679804801941,0.4345969124697148799896,\
 0.0417516361922025680542,0.4832747434265911579132,0.2889312515035271644592,\
 0.4115779171697795391083,0.2200270108878612518311,\
0.3144670636393129825592,0.2733902474865317344666,0.7691849744878709316254,\
 0.0548522863537073135376,0.4532337454147636890411,0.2262856932356953620911,\
 0.1486739399842917919159,0.2435002401471138000488,\
0.384454759303480386734,0.1141278846189379692078,0.3649685769341886043549,\
 0.9379479344934225082398,0.2138825734145939350128,0.8807754451408982276917,\
 0.3025345797650516033173,0.2935827709734439849854,\
0.9067896143533289432526,0.7959460681304335594177,0.0202379724942147731781,\
 0.1722054202109575271606,0.2199751031585037708283,0.7548991339281201362610,\
 0.4089378821663558483124,0.4680796265602111816406,\
0.420881266240030527115,0.7480402020737528800964,0.2455636872909963130951,\
 0.0257788877934217453003,0.3875689213164150714874,0.2191973784938454627991,\
 0.9874265412800014019013,0.6185800097882747650147,\
0.1833024383522570133209,0.5313195576891303062439,0.1505152708850800991058,\
 0.9561535362154245376587,0.6994940754957497119904,0.2583465399220585823059,\
 0.6155266496352851390839,0.1903010532259941101074,\
0.4607576900161802768707,0.5220010234043002128601,0.7053800462745130062103,\
 0.8874893691390752792358,0.1858218242414295673370,0.0922524714842438697815,\
 0.3779664481990039348602,0.9369315691292285919190}
#define ZINI8 {0.1980521664954721927643,0.4702028548344969749451,0.3778818598948419094086,\
 0.3629649449139833450317,0.2793333870358765125275,0.6721442686393857002258,\
 0.6908950763754546642304,0.5104757994413375854492,\
0.0610603489913046360016,0.9335384247824549674988,0.1448998316191136837006,\
 0.5721211265772581100464,0.5459886942990124225617,0.0516680190339684486389,\
 0.5011013220064342021942,0.9260971657931804656982,\
0.8546948046423494815826,0.5857099732384085655212,0.8791871047578752040863,\
 0.2532048318535089492798,0.790395137388259172440,0.6329805525019764900208,\
 0.8602323713712394237518,0.9019620195031166076660,\
0.3158749365247786045075,0.4001023573800921440125,0.1110895960591733455658,\
 0.4705127831548452377319,0.5362763185985386371613,0.2878431910648941993713,\
 0.8740125591866672039032,0.0740833915770053863525,\
0.2814957336522638797760,0.7083768015727400779724,0.1652647457085549831390,\
 0.2667352575808763504028,0.8819408011622726917267,0.3537154989317059516907,\
 0.0264621186070144176483,0.0861647427082061767578,\
0.2313965209759771823883,0.1340646473690867424011,0.6724002673290669918060,\
 0.1902998369187116622925,0.7307508592493832111359,0.5048490324988961219788,\
 0.8791159312240779399872,0.5544437132775783538818,\
0.2063297093845903873444,0.401161103509366512299,0.4559328979812562465668,\
 0.6977151576429605484009,0.3965912279672920703888,0.498381090350449085236,\
 0.1452422770671546459198,0.9075358733534812927246,\
0.1009295457042753696442,0.0177189959213137626648,0.7937671481631696224213,\
 0.4309146609157323837280,0.584337853360921144485,0.7954284632578492164612,\
 0.1390615846030414104462,0.1012784726917743682861}
#define ZRESR8 -0.2866880544829432109211
#define ZRESI8 -0.5082321435837643397449

#define ZINR10 {0.3316808626987040042877,0.8344425177201628684998,0.0549940518103539943695,\
 0.3696003425866365432739,0.7453266424126923084259,0.0571811841800808906555,\
 0.5999651807360351085663,0.2085741907358169555664,0.8798878290690481662750,\
 0.4782809792086482048035,\
0.7116099162958562374115,0.8585865031927824020386,0.8078222130425274372101,\
 0.5159962782636284828186,0.8917340408079326152802,0.8842348866164684295654,\
 0.70964269945397973061,0.6610225578770041465759,0.7252350724302232265472,\
 0.510143497958779335022,\
0.2824866441078484058380,0.2214915128424763679504,0.5767575385980308055878,\
 0.7048253491520881652832,0.5607945644296705722809,0.3628880484029650688171,\
 0.3088326244615018367767,0.9813414867967367172241,0.7428482254035770893097,\
 0.1616391474381089210510,\
0.3652521963231265544891,0.3835070468485355377197,0.1169181005097925662994,\
 0.8911246126517653465271,0.0634272000752389431000,0.6263941843062639236450,\
 0.6807702076621353626251,0.2588596837595105171204,0.4394804346375167369843,\
 0.8598818778991699218750,\
0.5482823201455175876617,0.8135995296761393547058,0.4898237003944814205170,\
 0.0240026097744703292847,0.7369195525534451007843,0.2411156157031655311585,\
 0.1529693226329982280731,0.2648359201848506927490,0.4298193217255175113678,\
 0.7673939457163214683533,\
0.8753260499797761440277,0.3796988371759653091431,0.3062356826849281787872,\
 0.3880051793530583381653,0.1047293278388679027557,0.7603831812739372253418,\
 0.0340930395759642124176,0.1423966242000460624695,0.5554559468291699886322,\
 0.8031897451728582382202,\
0.5183992316015064716339,0.1518561029806733131409,0.5884730662219226360321,\
 0.2545093484222888946533,0.9992679939605295658112,0.6398976957425475120544,\
 0.5506716123782098293304,0.4607007671147584915161,0.5933007937856018543243,\
 0.6538193570449948310852,\
0.4168340521864593029022,0.9910155385732650756836,0.3720780410803854465485,\
 0.7061824081465601921082,0.5780865414999425411224,0.602319641038775444031,\
 0.5715096746571362018585,0.0549629041925072669983,0.1205854485742747784,\
 0.0143620483577251434326,\
0.0257951230742037296295,0.8411248764023184776306,0.4381882525049149990082,\
 0.4643401596695184707642,0.4197426405735313892365,0.8023654492571949958801,\
 0.5228588166646659374237,0.5095121040940284729004,0.4531980180181562900543,\
 0.7817818326875567436218,\
0.776557037141174077988,0.0466059204190969467163,0.5113326688297092914581,\
 0.7502101892605423927307,0.6883628661744296550751,0.0167756117880344390869,\
 0.9345410899259150028229,0.5609863763675093650818,0.2205847105942666530609,\
 0.7648540753871202468872}
#define ZINI10 {0.4816976976580917835236,0.1558785634115338325501,0.2476022052578628063202,\
 0.5216529071331024169922,0.0805230387486517429352,0.4409417239949107170105,\
 0.8911933614872395992279,0.9780590813606977462769,0.4588093762286007404327,\
 0.5510440031066536903381,\
0.0960960905067622661591,0.4196785055100917816162,0.7502556503750383853912,\
 0.7218149593099951744080,0.2895541018806397914887,0.3907764498144388198853,\
 0.6686618146486580371857,0.4877656819298863410950,0.4685971769504249095917,\
 0.3562648519873619079590,\
0.3442325466312468051910,0.4253307832404971122742,0.5588058172725141048431,\
 0.3304864969104528427124,0.4157403339631855487824,0.1595822656527161598206,\
 0.3883102680556476116180,0.9415460713207721710205,0.4722979352809488773346,\
 0.8533652639016509056091,\
0.1207739165984094142914,0.8999380934983491897583,0.4384902161546051502228,\
 0.8976056622341275215149,0.4911110657267272472382,0.3402217179536819458008,\
 0.9966153600253164768219,0.0215395865961909294128,0.6876890822313725948334,\
 0.0044924151152372360229,\
0.6397854541428387165070,0.5416147718206048011780,0.2247649203054606914520,\
 0.7364005260169506072998,0.4496364505030214786530,0.9678138038143515586853,\
 0.6489060199819505214691,0.2544666919857263565064,0.1923975017853081226349,\
 0.6861492367461323738098,\
0.4231455805711448192596,0.6734441593289375305176,0.8270696722902357578278,\
 0.9360805852338671684265,0.8326222090981900691986,0.7424779590219259262085,\
 0.0194640238769352436066,0.8016031915321946144104,0.2554539437405765056610,\
 0.2688109613955020904541,\
0.7558490769006311893463,0.4347589677199721336365,0.6425966522656381130219,\
 0.6957868058234453201294,0.6499576461501419544220,0.2303190128877758979797,\
 0.5504368054680526256561,0.3038997054100036621094,0.0371030517853796482086,\
 0.1703881053254008293152,\
0.5698686256073415279388,0.0036411266773939132690,0.4491547052748501300812,\
 0.0576810697093605995178,0.4956056098453700542450,0.1888933442533016204834,\
 0.5641230703331530094147,0.8562210192903876304627,0.0794764286838471889496,\
 0.6196198705583810806274,\
0.2241039988584816455841,0.8582094730809330940247,0.7114551994018256664276,\
 0.8026027604937553405762,0.6153324418701231479645,0.8958183480426669120789,\
 0.8721761344932019710541,0.8389767911285161972046,0.2040955354459583759308,\
 0.3166538262739777565002,\
0.7006825651042163372040,0.2073105163872241973877,0.5222550616599619388580,\
 0.9416420971974730491638,0.52116033947095274925,0.4509841967374086380005,\
 0.3961292845197021961212,0.7240869747474789619446,0.6724055963568389415741,\
 0.2386146038770675659180}
#define ZRESR10 -0.0701164785573487325809
#define ZRESI10 -0.3697118554850691296565

static void ddetermaTest(void){
	double in2[]=IN2; double res2=RES2;
	double in3[]=IN3; double res3=RES3;
	double in4[]=IN4; double res4=RES4;
	double in5[]=IN5; double res5=RES5;
	double in6[]=IN6; double res6=RES6;
	double in8[]=IN8; double res8=RES8;
	double in10[]=IN10; double res10=RES10;
	double out2,out3,out4,out5,out6,out8,out10;
		printf("\n >>> DDetermA <<<\n");
	out2=ddeterma(in2,2);
	out3=ddeterma(in3,3);
	out4=ddeterma(in4,4);
	out5=ddeterma(in5,5);
	out6=ddeterma(in6,6);
	out8=ddeterma(in8,8);
	out10=ddeterma(in10,10);
	
	assert((fabs(out2-res2)/fabs(out2))<3e-8);
	assert((fabs(out3-res3)/fabs(out3))<3e-15);
	assert((fabs(out4-res4)/fabs(out4))<3e-15);
	assert((fabs(out5-res5)/fabs(out5))<3e-15);
	assert((fabs(out6-res6)/fabs(out6))<3e-15);
	assert((fabs(out8-res8)/fabs(out8))<3e-15);
	assert((fabs(out10-res10)/fabs(out10))<3e-15);
}

static void zdetermaTest(void){
	double inR2[]=ZINR2; double inI2[]=ZINI2; double resR2=ZRESR2;  double resI2=ZRESI2;
	double inR3[]=ZINR3; double inI3[]=ZINI3; double resR3=ZRESR3;  double resI3=ZRESI3;
	double inR4[]=ZINR4; double inI4[]=ZINI4; double resR4=ZRESR4;  double resI4=ZRESI4;
	double inR5[]=ZINR5; double inI5[]=ZINI5; double resR5=ZRESR5;  double resI5=ZRESI5;
	double inR6[]=ZINR6; double inI6[]=ZINI6; double resR6=ZRESR6;  double resI6=ZRESI6;
	double inR8[]=ZINR8; double inI8[]=ZINI8; double resR8=ZRESR8;  double resI8=ZRESI8;
	double inR10[]=ZINR10; double inI10[]=ZINI10; double resR10=ZRESR10;  double resI10=ZRESI10;
	doubleComplex out2,out3,out4,out5,out6,out8,out10;	
	doubleComplex *in2, *in3, *in4, *in5, *in6, *in8, *in10;
		printf("\n >>> ZDetermA <<<\n");
	in2=DoubleComplexMatrix(inR2,inI2,4);
	in3=DoubleComplexMatrix(inR3,inI3,9);
	in4=DoubleComplexMatrix(inR4,inI4,16);
	in5=DoubleComplexMatrix(inR5,inI5,25);
	in6=DoubleComplexMatrix(inR6,inI6,36);
	in8=DoubleComplexMatrix(inR8,inI8,64);
	in10=DoubleComplexMatrix(inR10,inI10,100);
	
	out2=zdeterma(in2,2);
	out3=zdeterma(in3,3);
	out4=zdeterma(in4,4);
	out5=zdeterma(in5,5);
	out6=zdeterma(in6,6);
	out8=zdeterma(in8,8);
	out10=zdeterma(in10,10);
	
	
	assert((fabs(zreals(out2)-resR2)/fabs(zreals(out2)))<3e-16);
	assert((fabs(zimags(out2)-resI2)/fabs(zimags(out2)))<3e-16);
	
	assert((fabs(zreals(out3)-resR3)/fabs(zreals(out3)))<3e-16);
	assert((fabs(zimags(out3)-resI3)/fabs(zimags(out3)))<1e-16);
	
	assert((fabs(zreals(out4)-resR4)/fabs(zreals(out4)))<3e-16);
	assert((fabs(zimags(out4)-resI4)/fabs(zimags(out4)))<3e-15);
	
	assert((fabs(zreals(out5)-resR5)/fabs(zreals(out5)))<3e-15);
	assert((fabs(zimags(out5)-resI5)/fabs(zimags(out5)))<3e-15);
	
	assert((fabs(zreals(out6)-resR6)/fabs(zreals(out6)))<3e-15);
	assert((fabs(zimags(out6)-resI6)/fabs(zimags(out6)))<3e-12);
	
	assert((fabs(zreals(out8)-resR8)/fabs(zreals(out8)))<3e-15);
	assert((fabs(zimags(out8)-resI8)/fabs(zimags(out8)))<3e-15);
	
	assert((fabs(zreals(out10)-resR10)/fabs(zreals(out10)))<3e-14);
	assert((fabs(zimags(out10)-resI10)/fabs(zimags(out10)))<3e-15);
}

static int determTest(void){
	printf("\n >>> Double Determ <<<\n");
	ddetermaTest();
	zdetermaTest();
	return 0;
}


int main (void){
	assert(determTest()==0);
	return 0;
}	