#!/usr/bin/perl
use strict;
use warnings;
use Data::Dumper;
use Bio::PhyloXS;
use Bio::Phylo::IO 'parse_tree';

my $tree = parse_tree(
	'-format' => 'newick',
	'-handle' => \*DATA,	
);
print $tree->to_newick;

__DATA__
((((((Galago_matschiei:3.6487,Euoticus_elegantulus:3.6487)205:4.86839,(Galagoides_zanzibaricus:3.57452,Galagoides_demidoff:3.57452)204:4.94257)206:0,((Otolemur_garnettii:4.24098,Otolemur_crassicaudatus:4.24098)202:4.27605,(Galago_alleni:5.39749,(Galago_gallarum:2.37158,(Galago_senegalensis:2.37158,Galago_moholi:2.37158):0)200:3.02591)201:3.11953)203:6.3e-05)207:12.4029,((Perodicticus_potto:4.69815,Arctocebus_calabarensis:4.69815)198:11.6497,(Loris_tardigradus:9.19418,(Nycticebus_pygmaeus:2.67234,Nycticebus_coucang:2.67234)196:6.52184)197:7.15369)199:4.57209)208:30.947,(Daubentonia_madagascariensis:39.4781,((((Lepilemur_mustelinus:11.204,(Lepilemur_septentrionalis:7.59107,(Lepilemur_ruficaudatus:5.02272,(Lepilemur_leucopus:3.00227,(Lepilemur_edwardsi:1.36641,Lepilemur_dorsalis:1.36641)187:1.63585)188:2.02045)189:2.56836)190:3.61297)191:5.96676,((Lemur_catta:6.23214,(Hapalemur_simus:5.66714,(Hapalemur_griseus:5.66714,Hapalemur_aureus:5.66714)183:0)184:0.564998)185:6.82367,(Varecia_variegata:11.8914,((Eulemur_rubriventer:3.06633,Eulemur_mongoz:3.06633)180:3.30316,(Eulemur_coronatus:3.75439,(Eulemur_macaco:3.67779,Eulemur_fulvus:3.67779)178:0.076596)179:2.6151)181:5.52195)182:1.16437)186:4.11499)192:4.87015,(Avahi_laniger:13.6107,(Indri_indri:7.43976,(Propithecus_diadema:5.87211,(Propithecus_verreauxi:1.53414,Propithecus_tattersalli:1.53414)174:4.33796)175:1.56766)176:6.17095)177:8.43024)193:5.47858,(Phaner_furcifer:17.0297,((Allocebus_trichotis:7.06198,(Microcebus_coquereli:4.09388,(Microcebus_rufus:2.72926,Microcebus_murinus:2.72926)169:1.36463)170:2.9681)171:4.40131,(Cheirogaleus_medius:9.40743,Cheirogaleus_major:9.40743)168:2.05586)172:5.56638)173:10.4899)194:11.9586)195:12.3889)209:13.2309,(((Tarsius_spectrum:15.9897,Tarsius_pumilus:15.9897)165:22.2262,(Tarsius_syrichta:16.0795,Tarsius_bancanus:16.0795)164:22.1364)166:24.3931,(((((((Chiropotes_satanas:3.67922,Chiropotes_albinasus:3.67922)72:4.4452,(Cacajao_melanocephalus:3.70937,Cacajao_calvus:3.70937)71:4.41505)73:3.76178,(Pithecia_pithecia:10.2411,(Pithecia_irrorata:6.55105,(Pithecia_aequatorialis:3.7806,(Pithecia_monachus:1.7649,Pithecia_albicans:1.7649)67:2.0157)68:2.77045)69:3.69002)70:1.64513)74:9.08215,(Callicebus_torquatus:16.4794,((Callicebus_modestus:7.32728,(Callicebus_donacophilus:3.08081,(Callicebus_olallae:3.08081,Callicebus_oenanthe:3.08081):0)63:4.24647)64:5.97682,(Callicebus_personatus:10.2952,((Callicebus_dubius:4.72722,(Callicebus_cupreus:1.99105,Callicebus_caligatus:1.99105)59:2.73618)60:3.26611,((Callicebus_hoffmannsi:2.35725,Callicebus_brunneus:2.35725)57:2.97278,(Callicebus_moloch:2.32718,Callicebus_cinerascens:2.32718)56:3.00284)58:2.66331)61:2.30191)62:3.00885)65:3.17531)66:4.48894)75:4.35162,((Alouatta_palliata:12.7369,(Alouatta_caraya:6.92023,(Alouatta_pigra:5.71088,(Alouatta_fusca:3.41788,(Alouatta_seniculus:1.61131,Alouatta_belzebul:1.61131)50:1.80657)51:2.293)52:1.20935)53:5.81666)54:7.95138,(((Ateles_paniscus:4.7004,(Ateles_marginatus:2.8909,Ateles_chamek:2.8909)47:1.8095):0,(Ateles_belzebuth:2.04664,(Ateles_geoffroyi:1.2092,Ateles_fusciceps:1.2092)45:0.837439)46:2.65376)48:6.59583,(Brachyteles_arachnoides:9.03194,(Lagothrix_lagotricha:2.91317,Lagothrix_flavicauda:2.91317)43:6.11876)44:2.26429)49:9.39204)55:4.6317)76:4.83535,((((Cebus_olivaceus:3.9671,Cebus_apella:3.9671)39:3.30047,(Cebus_capucinus:0.138835,Cebus_albifrons:0.138835)38:7.12873)40:15.9199,(Saimiri_boliviensis:8.42997,(Saimiri_vanzolinii:6.82962,(Saimiri_sciureus:3.94673,(Saimiri_ustus:1.75833,Saimiri_oerstedii:1.75833)34:2.1884)35:2.88289)36:1.60036)37:14.7575)41:2.49736,((Aotus_lemurinus:15.7892,((Aotus_vociferans:4.52261,Aotus_brumbacki:4.52261)30:7.23237,(Aotus_nancymaae:8.67574,(Aotus_miconax:6.28365,(Aotus_infulatus:4.15512,(Aotus_nigriceps:2.62541,(Aotus_trivirgatus:1.23196,Aotus_azarai:1.23196)25:1.39346)26:1.52971)27:2.12853)28:2.39208)29:3.07924)31:4.0342)32:6.24331,((Callimico_goeldii:18.3758,((Callithrix_pygmaea:3.71312,(Callithrix_humeralifera:2.07107,Callithrix_argentata:2.07107)20:1.64205)21:7.64608,((Callithrix_flaviceps:3.42958,Callithrix_aurita:3.42958)18:7.77439,((Callithrix_kuhlii:0.255971,Callithrix_geoffroyi:0.255971)16:0.255971,(Callithrix_penicillata:0.255971,Callithrix_jacchus:0.255971)15:0.255971)17:10.692)19:0.15523)22:7.01664)23:0.61583,((Leontopithecus_chrysomela:7.68227,(Leontopithecus_rosalia:3.84113,Leontopithecus_chrysopygus:3.84113)12:3.84113)13:7.97001,(((Saguinus_oedipus:3.27237,Saguinus_geoffroyi:3.27237)2:4.60936,(Saguinus_midas:3.31401,Saguinus_bicolor:3.31401)1:4.56772)3:4.80046,(Saguinus_leucopus:9.81891,((Saguinus_imperator:4.38323,(Saguinus_mystax:1.96062,Saguinus_labiatus:1.96062)7:2.42262)8:3.29356,(Saguinus_inustus:5.07181,(Saguinus_nigricollis:3.03334,(Saguinus_tripartitus:1.37792,Saguinus_fuscicollis:1.37792)4:1.65542)5:2.03846)6:2.60499)9:2.14212)10:2.86327)11:2.9701)14:3.33939)24:3.04082)33:3.65237)42:4.47046)77:21.0781,(((Pongo_pygmaeus:15.8431,(Gorilla_gorilla:6.41388,(Homo_sapiens:5.06909,(Pan_troglodytes:1.96134,Pan_paniscus:1.96134)88:3.10775)89:1.34478)90:9.42917)91:3.79517,((Hylobates_hoolock:4.01629,(Hylobates_pileatus:3.54814,((Hylobates_muelleri:0.888868,Hylobates_klossii:0.888868)83:2.65928,(Hylobates_moloch:3.52014,(Hylobates_lar:3.10557,Hylobates_agilis:3.10557)81:0.414571)82:0.028005)84:0)85:0.468146)86:1.8623,(Hylobates_syndactylus:4.01629,(Hylobates_gabriellae:1.80439,(Hylobates_leucogenys:0.792181,Hylobates_concolor:0.792181)78:1.01221)79:2.2119)80:1.8623)87:13.7596)92:12.7722,(((((((Trachypithecus_geei:5.13229,(Trachypithecus_auratus:3.73589,(Trachypithecus_francoisi:2.9008,((Trachypithecus_phayrei:0.696042,Trachypithecus_obscurus:0.696042)152:0.105296,(Trachypithecus_pileatus:0.801338,Trachypithecus_cristatus:0.801338):0)153:2.09946)154:0.835097)155:1.39639)156:1.8002,(Semnopithecus_entellus:6.93249,(Trachypithecus_vetulus:6.93249,Trachypithecus_johnii:6.93249)150:0)151:0):0,(Presbytis_potenziani:3.80452,(Presbytis_comata:1.59536,(Presbytis_frontata:1.59536,(Presbytis_rubicunda:1.59536,Presbytis_melalophos:1.59536):0):0)148:2.20916)149:3.12797)157:1.94541,(Pygathrix_nemaeus:8.00146,(Pygathrix_avunculus:3.87341,(Pygathrix_roxellana:2.60449,(Pygathrix_brelichi:1.03551,Pygathrix_bieti:1.03551)144:1.56897)145:1.26892)146:4.12805)147:0.876439)158:0.018766,(Nasalis_larvatus:3.48278,Nasalis_concolor:3.48278)143:5.41388)159:4.7058,((Procolobus_verus:5.25647,(Procolobus_pennantii:2.23774,Procolobus_badius:2.23774)140:3.01873)141:6.70346,(Colobus_satanas:6.03035,(Colobus_angolensis:3.48634,(Colobus_polykomos:0.800086,Colobus_guereza:0.800086)137:2.68625)138:2.54401)139:5.92958)142:1.64253)160:4.72766,(((((Mandrillus_sphinx:1.95826,Mandrillus_leucophaeus:1.95826)132:3.48489,(Cercocebus_torquatus:2.31318,Cercocebus_galeritus:2.31318)131:3.12998)133:1.27118,(Lophocebus_albigena:2.23338,(Theropithecus_gelada:1.5475,Papio_hamadryas:1.5475)129:0.685872)130:4.48096)134:2.51682,(Macaca_sylvanus:7.48375,((((Macaca_tonkeana:0.13504,Macaca_maura:0.13504)124:2.51899,(Macaca_ochreata:1.64531,Macaca_nigra:1.64531)123:1.00871)125:0.928615,(Macaca_silenus:2.25042,Macaca_nemestrina:2.25042)122:1.33223)126:2.6771,((Macaca_arctoides:2.80067,((Macaca_radiata:0.70926,Macaca_assamensis:0.70926)118:1.00024,(Macaca_thibetana:1.04751,Macaca_sinica:1.04751)117:0.661986)119:1.09117)120:1.63327,(Macaca_fascicularis:2.2216,(Macaca_fuscata:0.908084,(Macaca_mulatta:0.27622,Macaca_cyclopis:0.27622)114:0.631864)115:1.31352)116:2.21233)121:1.82581)127:1.22401)128:1.74741)135:2.02797,(Allenopithecus_nigroviridis:8.29204,(Miopithecus_talapoin:6.75124,((Erythrocebus_patas:5.17992,Chlorocebus_aethiops:5.17992)93:0.544109,((Cercopithecus_solatus:0.839612,(Cercopithecus_preussi:8.6e-05,Cercopithecus_lhoesti:8.6e-05)108:0.839526)109:4.08135,(Cercopithecus_hamlyni:4.22004,((Cercopithecus_neglectus:2.5642,((Cercopithecus_mona:0.789489,Cercopithecus_campbelli:0.789489)103:0.459721,(Cercopithecus_wolfi:0.769316,Cercopithecus_pogonias:0.769316)102:0.479894)104:1.31499)105:1.07305,((((Cercopithecus_erythrotis:1.04034,(Cercopithecus_cephus:0.490956,Cercopithecus_ascanius:0.490956)96:0.549383)97:0.664222,(Cercopithecus_petaurista:0.760628,Cercopithecus_erythrogaster:0.760628)95:0.943933)98:0.627724,(Cercopithecus_nictitans:0.96245,Cercopithecus_mitis:0.96245)94:1.36984)99:0.624653,(Cercopithecus_dryas:1.23689,Cercopithecus_diana:1.23689)100:1.72005)101:0.680311)106:0.582791)107:0.700924)110:0.803068)111:1.0272)112:1.54081)113:2.96708)136:7.071)161:14.0803)162:18.8231)163:11.3755)167:2.48889)210;