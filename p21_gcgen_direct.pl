#use List::Util qw(min max);
print("Hellow world!!!\n");

$RootDir = "log3031";
$exe = "direct_opt_test.exe"; #"examin_d.exe"
mkdir "$RootDir";

@dists=( "0.9", "0.9", "0.66", "0.9", "0.66", "0.9", "0.66", "0.66", "0.9", "0.9", "0.9" );
@radiuss=( "0.2", "0.1", "0.2", "0.2", "0.2", "0.2", "0.3", "0.2", "0.2", "0.2", "0.2" );
@dims=( "2", "2", "3", "3", "4", "4", "5", "5", "6", "7", "8" );
@epss=( "0.01", "0.01", "0.01", "0.01", "0.03", "0.03", "0.03", "0.03", "0.0464", "0.0517", "0.0562" );
@shs=( "simple", "hard", "simple", "hard", "simple", "hard", "simple", "hard", "simple", "simple", "simple" );
@rs=( "4.5", "5.6", "4.5", "5.6", "4.5", "5.6", "4.5", "5.6", "5.6", "5.6", "5.6" );
@nls=(1, 2);
@kdims=(0, 0, 1);
@epssloc=(0.0001, 0.0005, 0.001, 0.005, 0.01);
@function_classes = ("Shekel" , "Hill");

@par = (1, 100);
$indexPar = 0;
while ($arg = shift @ARGV)
{
	$par[$indexPar] = int($arg);
	$indexPar++;
	#print “$arg\n”;
}

$l=9;
$npl=256;

$startZad = $par[0];
$zad=$par[1];


$rm=6;
$N=4;
$l1=1;
$l2=1;

$k=0;
$numlev=2;
$r0=2.0;
$r1=4.2;

$localr0=2;
$localr1=30;

$eps0=0.0001;
$eps1=0.01;

$nt1 = 15;
$NumThread=1;

$nl=1;
$LN = 20;
$nc = 1;


	$dist=$dists[0];
	$radius=$radiuss[0];
	$N=$dims[0];
	#$eps=$epss[$i];
	$sh0=$shs[0];
	$r=$rs[0];

	$m=10; 
	$function_class = "Shekel";
	$i=1;
for ( $i=0 ; $i<=1; $i++ )
{

	#$dist=$dists[$i];
	#$radius=$radiuss[$i];
	#$N=$dims[$i];
	##$eps=$epss[$i];
	#$sh0=$shs[$i];
	#$r=$rs[$i];
	$function_class = $function_classes[$i];

	$m=10;
	$isCalculationInBorderPoint = 1;
	for ( $func=$startZad	; $func<=$zad; $func++ )
	{		
		$npl = 1;
		
		#for ( $NumThread=1 ; $NumThread<=$npl; $NumThread=$NumThread * 2 ) 
		{

			#for ( $eps=$eps0 ; $eps<=$eps1; $eps= $eps + 0.0001  )
			$eps = 0.001;
			#foreach $eps(@epssloc)
			{
				$te = 	0.0005;
				$r=2.8 ;
				#for ( $r=$r0 ; $r<=$r1; $r= $r+0.2  )
				{
				
				
					
					$NN = 1;
					$nmpi = $nc + 1;
					$Alpha = 0;
					$localMix = 5;
					#for ($Alpha = 15; $Alpha <= 35.1; $Alpha = $Alpha + 10)	
					{
					
					    #for ($localMix = 2; $localMix <= 4.1; $localMix = $localMix + 1)
						{
							#$dir = "${RootDir}\\GCGen_l_${function_class}_${NN}_${i}_${NumThread}_${r}_${eps}_${Alpha}_${localMix}_${isCalculationInBorderPoint}";
							#mkdir "$dir";
							#$argum1="$exe -lib GCGen.dll -NumPoints $NumThread -NumThread $NumThread  -TypeMethod 0 -m 10 -TypeCalculation 0 -function_number $func -global_dist $dist -global_radius $radius -Dimension $NN -Epsilon $eps -r $r -Comment GCGen_ -MaxNumOfPoints 100000_2_2_2 -stopCondition 5 -localVerificationType 0 -function_class $function_class -isUseLocalUpdate 0 -localMix $localMix -localAlpha $Alpha >${dir}\\GCGen_l_${function_class}_${NN}_${i}_${func}_${NumThread}_${r}_${eps}_${Alpha}_${localMix}_.txt";
							#print($argum1);
							#system $argum1;
							#print("\n");
							
							#$dir = "${RootDir}\\GCGen_0_${function_class}_${NN}_${i}_${NumThread}_${r}_${eps}_${Alpha}_${localMix}_${isCalculationInBorderPoint}";
							#mkdir "$dir";
							#$argum1="$exe -lib GCGen.dll -NumPoints $NumThread -NumThread $NumThread  -TypeMethod 0 -m 10 -TypeCalculation 0 -function_number $func -global_dist $dist -global_radius $radius -Dimension $NN -Epsilon $eps -r $r -Comment GCGen_ -MaxNumOfPoints 100000_2_2_2 -isCalculationInBorderPoint $isCalculationInBorderPoint -stopCondition 5 -localVerificationType 0 -function_class $function_class -isUseLocalUpdate 0 >${dir}\\GCGen_0_${function_class}_${NN}_${i}_${func}_${NumThread}_${r}_${eps}_${isCalculationInBorderPoint}_.txt";
							#print($argum1);
							#system $argum1;
							#print("\n");
						}
					}
				
					#$nt1 = $nt1 + 1;
					$TypeStartLocalMethod = 1;
					$TypeLocalMethod = 1;
					$PointTakingType = 1;
					$StatusIntervalChangeType = 0; 
					$TypeLocalMinIntervale = 2; #1-Дерево решения
					
					$DecisionTreesMaxDepth = 100000;
					$DecisionTreesRegressionAccuracy = 0.001;
					$countPointInLocalMinimum = 7;
					
					#for ($TypeLocalMethod = 0; $TypeLocalMethod <= 1; $TypeLocalMethod++)
					{
						$TypeAddLocalPoint = 1;
						#for ($TypeAddLocalPoint = 0; $TypeAddLocalPoint <= 1; $TypeAddLocalPoint++)
						{
						#for ($TypeStartLocalMethod = 0; $TypeStartLocalMethod <= 1; $TypeStartLocalMethod++)
							
							$localr= 1.0;
							#$localr= $r * $r * $r;
							$localr0 = $r * $r;
							$localr1 = $r * $r * $r;
							#for ( $localr=$localr0 ; $localr<=$localr1; $localr= $localr + $r  )
							#for ( $localr=$localr0 ; $localr<=$localr1; $localr= $localr * $r  )
							{
								$maxCountLocalPoint = 7 + (1 - $TypeLocalMethod) * 1000;								
                                
								$dir = "${RootDir}\\GCGen_1_${function_class}_${localr}_${NN}_${i}_${NumThread}_${r}_${TypeStartLocalMethod}__${eps}_${TypeLocalMethod}_${TypeAddLocalPoint}_${maxCountLocalPoint}_${PointTakingType}_${StatusIntervalChangeType}_${isCalculationInBorderPoint}_${DecisionTreesMaxDepth}_${DecisionTreesRegressionAccuracy}_";
								mkdir "$dir";
								
								#$argum1="$exe -lib GCGen.dll -NumPoints $NumThread -NumThread $NumThread  -TypeMethod 0 -m 10 -TypeCalculation 0 -function_number $func -global_dist $dist -global_radius $radius -Dimension $NN -Epsilon $eps -r $r -Comment GCGen_ -MaxNumOfPoints 100000_2_2_2 -isCalculationInBorderPoint $isCalculationInBorderPoint -stopCondition 5 -localVerificationType 1 -function_class $function_class -isUseLocalUpdate 1 -Localr $localr -TypeStartLocalMethod $TypeStartLocalMethod -TypeLocalMethod $TypeLocalMethod -TypeAddLocalPoint $TypeAddLocalPoint -maxCountLocalPoint $maxCountLocalPoint -PointTakingType $PointTakingType -StatusIntervalChangeType $StatusIntervalChangeType -TypeLocalMinIntervale $TypeLocalMinIntervale -DecisionTreesMaxDepth $DecisionTreesMaxDepth -DecisionTreesRegressionAccuracy $DecisionTreesRegressionAccuracy -countPointInLocalMinimum $countPointInLocalMinimum >${dir}\\GCGen_1_${function_class}_${localr}_${NN}_${i}_${func}_${NumThread}_${r}_${TypeStartLocalMethod}_${eps}__${TypeLocalMethod}_${TypeAddLocalPoint}_${maxCountLocalPoint}_${PointTakingType}_${StatusIntervalChangeType}_${isCalculationInBorderPoint}_${DecisionTreesMaxDepth}_${DecisionTreesRegressionAccuracy}__.txt";
								
								
								open(W, ">GCGen_conf_1.xml");
								print W 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<config>
  <function_number>${func}</function_number>
  <problem_class>Problem</problem_class>
  <function_class>${function_class}</function_class>
</config>";
										
								close(W);
								
								
								$argum1="$exe GCGen.dll GCGen_conf_1.xml>${dir}\\GCGen_1_${function_class}_${localr}_${NN}_${i}_${func}_${NumThread}_${r}_${TypeStartLocalMethod}_${eps}__${TypeLocalMethod}_${TypeAddLocalPoint}_${maxCountLocalPoint}_${PointTakingType}_${StatusIntervalChangeType}_${isCalculationInBorderPoint}_${DecisionTreesMaxDepth}_${DecisionTreesRegressionAccuracy}__.txt";
								
								print($argum1);
								system $argum1;
								print("\n");

							}	
						}
					}
				}
			}
		}
	}

}