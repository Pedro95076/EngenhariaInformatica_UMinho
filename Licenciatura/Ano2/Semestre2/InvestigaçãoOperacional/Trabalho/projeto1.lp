/* Objective function

Peso de todos os vertices a somar

	 I	     1	     2     	 3	      4	      5	      6	      7	     8	      9	      10	  11	  12	 13	      F
I	0,00	3,00	4,24	6,32	8,25	5,66	6,00	10,00	9,85	10,00	10,20	11,18	12,81	7,21	14,42
1		    0,00	3,00	6,08	8.06	4,12	3,00	8,54	7,21	7,00	7,28	8,60	10,63	5,00	12,04
2			        0,00	3,16	5.10	1,41	4,24	5,83	6,08	7,62	7,07	7,28	8,60	3,16	10,30
3				            0,00	2.00	2,83	7,21	4,47	7,28	10,00	8,94	8,06	8,25	4,47	10,20
4					                0,00	4.47	8.94	4.00	8.06	11.31	10.00	8.54	8.00	5.66	10.00
5						                    0,00	4,47	4,47	5,00	7,21	6,32	6,08	7,21	2,00	8,94
6							                        0,00	8,00	5,00	4,00	4,47	6,40	8,94	4,00	10,00
7								                            0,00	5,00	8,94	7,21	5,00	4,00	4,00	6,00
8									                                0,00	4,12	2,24	1,41	4,12	3,00	5,00
9										                                    0,00	2,00	5,00	8,00	5,66	8,25
10											                                        0,00	3,00	6,00	4,47	6,32
11												                                            0,00	3,00	4,12	3,61
12													                                                0,00	5,66	2,00
13														                                                    0,00	7,21
F															                                                        0,00


*/

min: p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9 + p10 + p11 + p12 + p13 + pi + pf;

/* Variable bounds

    arestas auxiliares: aif (inicio fim)
    arestas obrigatorias: oif (inicio fim)

*/

/*Inicial: Saidas maior q entradas*/

is=ai1 + ai2 + ai3 + ai4 + ai5 + ai6 + ai7 + ai8 + ai9 + ai10 + ai11 + ai12 + ai13 + aif + oi1 + oi4;
ie=a1i + a2i + a3i + a4i + a5i + a6i + a7i + a8i + a9i + a10i + a11i + a12i + a13i + afi + o1i + o4i;
is-1=ie;

/*Final: Entradas maior q saidas*/

fs=af1 + af2 + af3 + af4 + af5 + af6 + af7 + af8 + af9 + af10 + af11 + af12 + af13 + afi + of12 + of9;
fe=a1f + a2f + a3f + a4f + a5f + a6f + a7f + a8f + a9f + a10f + a11f + a12f + a13f + aif + o9f + o12f;
fe-1=fs;
/*Todos os restantes: saidas iguais a entradas*/

a12   + a13  + a14  + a15  + a16  + a17  + a18  + a19  + a110 + aum11 + a112  + a113  + a1i  + a1f     + o1i   + o12   + o16   = oi1   + o21   + o61   + a21   + a31  + a41  + a51  + a61  + a71  + a81  + a91  + a101 + a11um + a121  + a131  + ai1  + af1;
a21   + a23  + a24  + a25  + a26  + a27  + a28  + a29  + a210 + a211  + a212  + a213  + a2i  + a2f     + o21   + o23   + o25   = o12   + o32   + o52   + a12   + a32  + a42  + a52  + a62  + a72  + a82  + a92  + a102 + a112  + a122  + a132  + ai2  + af2;
a31   + a32  + a34  + a35  + a36  + a37  + a38  + a39  + a310 + a311  + a312  + a313  + a3i  + a3f     + o32   + o35   + o34   = o23   + o53   + o43   + a13   + a23  + a43  + a53  + a63  + a73  + a83  + a93  + a103 + a113  + a123  + a133  + ai3  + af3;
a41   + a42  + a43  + a45  + a46  + a47  + a48  + a49  + a410 + a411  + a412  + a413  + a4i  + a4f     + o4i   + o43   + o47   = oi4   + o34   + o74   + a14   + a24  + a34  + a54  + a64  + a74  + a84  + a94  + a104 + a114  + a124  + a134  + ai4  + af4;
a51   + a52  + a53  + a54  + a56  + a57  + a58  + a59  + a510 + a511  + a512  + a513  + a5i  + a5f     + o52   + o53           = o25   + o35           + a15   + a25  + a35  + a45  + a65  + a75  + a85  + a95  + a105 + a115  + a125  + a135  + ai5  + af5;
a61   + a62  + a63  + a64  + a65  + a67  + a68  + a69  + a610 + a611  + a612  + a613  + a6i  + a6f     + o61   + o69           = o16   + o96           + a16   + a26  + a36  + a46  + a56  + a76  + a86  + a96  + a106 + a116  + a126  + a136  + ai6  + af6;
a71   + a72  + a73  + a74  + a75  + a76  + a78  + a79  + a710 + a711  + a712  + a713  + a7i  + a7f     + o74   + o712  + o713  = o47   + o127  + o137  + a17   + a27  + a37  + a47  + a57  + a67  + a87  + a97  + a107 + a117  + a127  + a137  + ai7  + af7;
a81   + a82  + a83  + a84  + a85  + a86  + a87  + a89  + a810 + a811  + a812  + a813  + a8i  + a8f     + o810  + o811  + o813  = o108  + o118  + o138  + a18   + a28  + a38  + a48  + a58  + a68  + a78  + a98  + a108 + a118  + a128  + a138  + ai8  + af8;
a91   + a92  + a93  + a94  + a95  + a96  + a97  + a98  + a910 + a911  + a912  + a913  + a9i  + a9f     + o96   + o910  + o9f   = o69   + o109  + of9   + a19   + a29  + a39  + a49  + a59  + a69  + a79  + a89  + a109 + a119  + a129  + a139  + ai9  + af9;
a110  + a102 + a103 + a104 + a105 + a106 + a107 + a108 + a109 + a1011 + a1012 + a1013 + a10i + a10f    + o109  + o108  + o1011 = o910  + o810  + o1110 + a110  + a210 + a310 + a410 + a510 + a610 + a710 + a810 + a910 + a1110 + a1210 + a1310 + ai10 + af10;
a11um + a112 + a113 + a114 + a115 + a116 + a117 + a118 + a119 + a1110 + a1112 + a1113 + a11i + a11f    + o118  + o1110 + o1112 = o811  + o1011 + o1211 + aum11 + a211 + a311 + a411 + a511 + a611 + a711 + a811 + a911 + a1011 + a1211 + a1311 + ai11 + af11;
a121  + a122 + a123 + a124 + a125 + a126 + a127 + a128 + a129 + a1210 + a1211 + a1213 + a12i + a12f    + o1211 + o127  + o12f  = o1112 + o712  + of12  + a112  + a212 + a312 + a412 + a512 + a612 + a712 + a812 + a912 + a1012 + a1112 + a1312 + ai12 + af12;
a131  + a132 + a133 + a134 + a135 + a136 + a137 + a138 + a139 + a1310 + a1311 + a1312 + ai13 + a13f    + o138  + o137          = o813  + o713          + a113  + a213 + a313 + a413 + a513 + a613 + a713 + a813 + a913 + a1013 + a1113 + a1213 + ai13 + af13;

/*vertices em q e obrigatorio passar: x para y mais y para x igual a 1*/

o1i   + oi1   = 1;
o12   + o21   = 1;
o16   + o61   = 1;
o23   + o32   = 1;
o25   + o52   = 1;
o35   + o53   = 1;
o34   + o43   = 1;
o4i   + oi4   = 1;
o47   + o74   = 1;
o69   + o96   = 1;
o712  + o127  = 1;
o713  + o137  = 1;
o810  + o108  = 1;
o811  + o118  = 1;
o813  + o138  = 1;
o910  + o109  = 1;
o9f   + of9   = 1;
o1011 + o1110 = 1;
o1112 + o1211 = 1;
o12f  + of12  = 1;


/*Pesos*/

p1  =             3a12      + 6.08a13  + 8.06a14  + 4.12a15  + 3a16     + 8.54a17  + 7.21a18  + 7a19     + 7.28a110  + 8.60aum11 + 10.63a112 + 5a113     + 3a1i      + 12.04a1f  + 3o1i     + 3o12   + 3o16;
p2  = 3a21                  + 3.16a23  + 5.10a24  + 1.41a25  + 4.24a26  + 5.83a27  + 6.08a28  + 7.62a29  + 7.07a210  + 7.28a211  + 8.60a212  + 3.16a213  + 4.24a2i   + 10.30a2f  + 3o21     + 6o23   + 2o25;
p3  = 6.08a31   + 3.16a32              + 2a34     + 2.83a35  + 7.21a36  + 4.47a37  + 7.28a38  + 10a39    + 8.94a310  + 8.06a311  + 8.25a312  + 4.47a313  + 6.32a3i   + 10.20a3f  + 6o32     + 4o35   + 2o34;
p4  = 8.06a41   + 5.10a42   + 2a43                + 4.47a45  + 8.94a46  + 4a47     + 8.06a48  + 11.31a49 + 10a410    + 8.54a411  + 8a412     + 5.66a413  + 8.25a4i   + 10a4f     + 10o4i    + 2o43   + 4o47;
p5  = 4.12a51   + 1.41a52   + 2.83a53  + 4.47a54             + 4.47a56  + 4.47a57  + 5a58     + 7.21a59  + 6.32a510  + 6.08a511  + 7.21a512  + 2a513     + 5.66a5i   + 8.94a5f   + 2o52     + 4o53;
p6  = 3a61      + 4.24a62   + 7.21a63  + 8.94a64  + 4.47a65             + 8a67     + 5a68     + 4a69     + 4.47a610  + 6.4a611   + 8.94a612  + 4a613     + 6a6i      + 10a6f     + 3o61     + 4o69;
p7  = 8.54a71   + 5.83a72   + 4.47a73  + 4a74     + 4.47a75  + 8a76                + 5a78     + 8.94a79  + 7.21a710  + 5a711     + 4a712     + 4a713     + 10a7i     + 6a7f      + 4o74     + 4o712  + 4o713;
p8  = 7.21a81   + 6.08a82   + 7.28a83  + 8.06a84  + 5a85     + 5a86     + 5a87                + 4.12a89  + 2.24a810  + 1.41a811  + 4.12a812  + 3a813     + 9.85a8i   + 5a8f      + 3o810    + 2o811  + 3o813;
p9  = 7a91      + 7.62a92   + 10a93    + 11.31a94 + 7.21a95  + 4a96     + 8.94a97  + 4.12a98             + 2a910     + 5a911     + 8a912     + 5.66a913  + 10a9i     + 8.25a9f   + 4o96     + 2o910  + 10o9f;
p10 = 7.28a110  + 7.07a102  + 8.94a103 + 10a104   + 6.32a105 + 4.47a106 + 7.21a107 + 2.24a108 + 2a109                + 3a1011    + 6a1012    + 4.47a1013 + 10.2a10i  + 6.32a10f  + 2o109    + 3o108  + 5o1011;
p11 = 8.6a11um  + 7.28a112  + 8.06a113 + 8.54a114 + 6.08a115 + 6.4a116  + 5a117    + 1.41a118 + 5a119                            + 3a1110    + 3a1112    + 4.12a1113 + 11.18a11i + 3.61a11f + 2o118  + 5o1110 + 3o1112;
p12 = 10.63a121 + 8.6a122   + 8.25a123 + 8a124    + 7.21a125 + 8.94a126 + 4a127    + 4.12a128 + 8a129    + 6a1210    + 3a1211                + 5.66a1213 + 12.81a12i + 2a12f     + 3o1211   + 4o127  + 2o12f;
p13 = 5a131     + 3.16a132  + 4.47a133 + 5.66a134 + 2a135    + 4a136    + 4a137    + 3a138    + 5.66a139 + 4.47a1310 + 4.12a1311 + 5.66a1312             + 7.21ai13  + 2a13f     + 3o138    + 4o137;
pi  = 3ai1      + 4.24ai2   + 6.32ai3  + 8.25ai4  + 5.66ai5  + 6ai6     + 10ai7    + 9.85ai8  + 10ai9    + 10.20ai10 + 11.18ai11 + 12.81ai12 + 7.21ai13              + 14.42aif  + 3oi1     + 10oi4;
pf  = 14.42af1  + 12.04af2  + 10.3af3  + 10.2af4  + 10af5    + 8.94af6  + 10af7    + 6af8     + 5af9     + 8.25af10  + 6.32af11  + 3.61af12  + 2af13     + 7.21afi               + 2of12    + 10of9;

bin a12   , a13  , a14  , a15  , a16  , a17  , a18  , a19  , a110 , aum11 , a112  , a113  , a1i  , a1f     , o1i   , o12   , o16;
bin a21   , a23  , a24  , a25  , a26  , a27  , a28  , a29  , a210 , a211  , a212  , a213  , a2i  , a2f     , o21   , o23   , o25;
bin a31   , a32  , a34  , a35  , a36  , a37  , a38  , a39  , a310 , a311  , a312  , a313  , a3i  , a3f     , o32   , o35   , o34;
bin a41   , a42  , a43  , a45  , a46  , a47  , a48  , a49  , a410 , a411  , a412  , a413  , a4i  , a4f     , o4i   , o43   , o47;
bin a51   , a52  , a53  , a54  , a56  , a57  , a58  , a59  , a510 , a511  , a512  , a513  , a5i  , a5f     , o52   , o53;
bin a61   , a62  , a63  , a64  , a65  , a67  , a68  , a69  , a610 , a611  , a612  , a613  , a6i  , a6f     , o61   , o69;
bin a71   , a72  , a73  , a74  , a75  , a76  , a78  , a79  , a710 , a711  , a712  , a713  , a7i  , a7f     , o74   , o712  , o713;
bin a81   , a82  , a83  , a84  , a85  , a86  , a87  , a89  , a810 , a811  , a812  , a813  , a8i  , a8f     , o810  , o811  , o813;
bin a91   , a92  , a93  , a94  , a95  , a96  , a97  , a98  , a910 , a911  , a912  , a913  , a9i  , a9f     , o96   , o910  , o9f;
bin a110  , a102 , a103 , a104 , a105 , a106 , a107 , a108 , a109 , a1011 , a1012 , a1013 , a10i , a10f    , o109  , o108  , o1011;
bin a11um , a112 , a113 , a114 , a115 , a116 , a117 , a118 , a119 , a1110 , a1112 , a1113 , a11i , a11f    , o118  , o1110 , o1112;
bin a121  , a122 , a123 , a124 , a125 , a126 , a127 , a128 , a129 , a1210 , a1211 , a1213 , a12i , a12f    , o1211 , o127  , o12f;
bin a131  , a132 , a133 , a134 , a135 , a136 , a137 , a138 , a139 , a1310 , a1311 , a1312 , ai13 , a13f    , o138  , o137;
bin ai1   , ai2  , ai3  , ai4  , ai5  , ai6  , ai7  , ai8  , ai9  , ai10  , ai11  , ai12  , ai13 , aif     , oi1   , oi4;
bin af1   , af2  , af3  , af4  , af5  , af6  , af7  , af8  , af9  , af10  , af11  , af12  , af13 , afi     , of12  , of9;
int fs,fe,ie,is;
