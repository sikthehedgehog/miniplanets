<?php
   function makevoid($filename, $size) {
      $img = imagecreate(0x20, 0x20);
      
      imagecolorallocate($img, 0xFF, 0x00, 0xFF);
      imagecolorallocate($img, 0x00, 0xFF, 0xFF);
      imagecolorallocate($img, 0x00, 0xFF, 0xFF);
      imagecolorallocate($img, 0x00, 0xFF, 0xFF);
      
      imagecolorallocate($img, 0x22, 0x00, 0x00);
      imagecolorallocate($img, 0x22, 0x00, 0x00);
      imagecolorallocate($img, 0x22, 0x00, 0x00);
      imagecolorallocate($img, 0x44, 0x00, 0x00);
      imagecolorallocate($img, 0x44, 0x00, 0x00);
      imagecolorallocate($img, 0x44, 0x00, 0x00);
      imagecolorallocate($img, 0x66, 0x00, 0x00);
      imagecolorallocate($img, 0x66, 0x00, 0x00);
      imagecolorallocate($img, 0x66, 0x00, 0x00);
      imagecolorallocate($img, 0x88, 0x00, 0x00);
      imagecolorallocate($img, 0x88, 0x00, 0x00);
      imagecolorallocate($img, 0x88, 0x00, 0x00);
      
      for ($y = 0x00; $y < 0x10; $y++)
      for ($x = 0x00; $x < 0x10; $x++) {
         $ax = $x;
         $ay = $y;
         
         if (($x ^ $y) & 0x01)
            $ax = -$x;
         
         $dist = sqrt($ax*$ax + $ay*$ay + 1);
         
         $angle = atan2($ay + 1, $ax + 1);
         $angle = $angle / 3.1415926 * 180.0;
         if ($angle < 0) $angle += 360.0;
         
         $angle += $dist * 4;
         
         $angle *= 8;
         $angle %= 360;
         
         $destx = $x + 0x10;
         $desty = $y + 0x10;
         
         $angle /= 30;
         $angle += 4;
         imagesetpixel($img, $destx, $desty, $angle);
      }
      
      for ($y = 0x00; $y < 0x10; $y++)
      for ($x = 0x00; $x < 0x10; $x++) {
         $col = imagecolorat($img, $x + 0x10, $y + 0x10);
         imagesetpixel($img, 0x0F - $x, $y + 0x10, $col);
         imagesetpixel($img, $x + 0x10, 0x0F - $y, $col);
         imagesetpixel($img, 0x0F - $x, 0x0F - $y, $col);
      }
      
      for ($y = 0x00; $y < 0x20; $y++)
      for ($x = 0x00; $x < 0x20; $x++) {
         $ax = $x - 0x10;
         $ay = $y - 0x10;
         $dist = sqrt($ax*$ax + $ay*$ay + 1);
         
         if ($dist > rand() % 0x04 + $size + 1)
            imagesetpixel($img, $x, $y, 0);
      }
      
      imagepng($img, $filename);
   }
   
   makevoid("void_1a.png", 8);
   makevoid("void_1b.png", 8);
   makevoid("void_1c.png", 8);
   makevoid("void_1d.png", 8);
   makevoid("void_2a.png", 12);
   makevoid("void_2b.png", 12);
   makevoid("void_2c.png", 12);
   makevoid("void_2d.png", 12);
?>
