$fn=7;
echo (290-97.5);
breite=190;
tiefe=290-97.5;
difference(){
    union(){
        cube([breite,tiefe,1]);
        for (i=[5:10:breite]){
          for (j=[5:10:tiefe]){
              translate([i,j,0])cylinder(d=6,h=7);
          }
        }
    }    
    for (i=[10:5:breite-10]){
      for (j=[10:5:tiefe-10]){
         translate([i,j,-1])cylinder(d=3,h=13);
      }
    }    
}