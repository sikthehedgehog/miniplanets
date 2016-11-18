<?php
   $altpal = FALSE;
   $img = imagecreate(160, 112);
   
   if ($altpal) {
      imagecolorallocate($img, 0x00, 0x00, 0x00);
      
      imagecolorallocate($img, 0xAA, 0x00, 0x00);
      imagecolorallocate($img, 0xAA, 0x00, 0x22);
      imagecolorallocate($img, 0xAA, 0x00, 0x44);
      imagecolorallocate($img, 0xAA, 0x00, 0x66);
      imagecolorallocate($img, 0xAA, 0x00, 0x88);
      
      imagecolorallocate($img, 0xAA, 0x00, 0xAA);
      imagecolorallocate($img, 0xAA, 0x22, 0x88);
      imagecolorallocate($img, 0xAA, 0x44, 0x66);
      imagecolorallocate($img, 0xAA, 0x66, 0x44);
      imagecolorallocate($img, 0xAA, 0x88, 0x22);
      
      imagecolorallocate($img, 0xAA, 0xAA, 0x00);
      imagecolorallocate($img, 0xAA, 0x88, 0x00);
      imagecolorallocate($img, 0xAA, 0x66, 0x00);
      imagecolorallocate($img, 0xAA, 0x44, 0x00);
      imagecolorallocate($img, 0xAA, 0x22, 0x00);
   }
   else {
      imagecolorallocate($img, 0x00, 0x00, 0x00);
      
      imagecolorallocate($img, 0x66, 0x00, 0x00);
      imagecolorallocate($img, 0x66, 0x22, 0x00);
      imagecolorallocate($img, 0x66, 0x44, 0x00);
      
      imagecolorallocate($img, 0x66, 0x66, 0x00);
      imagecolorallocate($img, 0x66, 0x44, 0x22);
      imagecolorallocate($img, 0x66, 0x22, 0x44);
      
      imagecolorallocate($img, 0x66, 0x00, 0x66);
      imagecolorallocate($img, 0x44, 0x00, 0x66);
      imagecolorallocate($img, 0x22, 0x00, 0x66);
      
      imagecolorallocate($img, 0x00, 0x00, 0x66);
      imagecolorallocate($img, 0x00, 0x22, 0x66);
      imagecolorallocate($img, 0x00, 0x44, 0x66);
      
      imagecolorallocate($img, 0x00, 0x66, 0x66);
      imagecolorallocate($img, 0x22, 0x44, 0x44);
      imagecolorallocate($img, 0x44, 0x22, 0x22);
   }
   
   for ($y = 0; $y < 112; $y++)
   for ($x = 0; $x < 160; $x++) {
      $ax = $x;
      $ay = $y;
      
      if (($x ^ $y) & 0x01)
         $ax = -$x;
      
      $dist = sqrt($ax*$ax + $ay*$ay + 1);
      
      $angle = atan2($ay + 1, $ax + 1);
      $angle = $angle / 3.1415926 * 180.0;
      if ($angle < 0) $angle += 360.0;
      $angle += $dist / 2;
      
      $angle *= 8;
      $angle %= 360;
      
      $destx = $x;
      $desty = $y;
      
      $angle /= 24;
      $angle += 1;
      imagesetpixel($img, $destx, $desty, $angle);
   }
   
   imagepng($img, "stage6_bg.png");
?>
