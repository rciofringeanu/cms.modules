<?php if(!empty($images)): ?>    
    <div id="myCarousel" class="carousel slide img-polaroid species-carousel">
        <!-- Carousel items -->
        <?php if(count($images) > 1): ?><a class="carousel-control left" href="#myCarousel" data-slide="prev">&lsaquo;</a><?php endif; ?>
        <div class="carousel-inner">
            <div class="active item">                    
                <?php if ('arkive' == $image_type): ?>
                    <?php echo $images[0];
                    unset($images[0]); ?>
                <?php elseif ('cck' == $image_type): ?>
                    <img src="<?php echo file_create_url($images['und'][0]['uri']); ?>" alt="" title="" class="species-custom-image" />                                    
                <?php endif; ?>                
            </div>
            <?php if(count($images) > 1): ?>                
                <?php foreach ($images as $index => $image): ?>
                    <div class="item">
                        <?php if ('arkive' == $image_type): ?>
                            <?php echo $image; ?>
                        <?php elseif ('cck' == $image_type): ?>
                            <img src="<?php echo file_create_url($image['uri']); ?>" alt="" title="" class="species-custom-image" />
                        <?php endif; ?>
                    </div>
                <?php endforeach; ?>                
            <?php endif; ?>
        </div>
        <?php if(count($images) > 1): ?><a class="carousel-control right" href="#myCarousel" data-slide="next">&rsaquo;</a><?php endif; ?>
    </div> 
    <p class="species-custom-image-author"><?php echo l($title, drupal_lookup_path('alias', 'node/'.$nid)); ?></p>
<?php else: ?>
    <div class="alert alert-info species-alert">
        <p><?php echo t('No pictures for ') . $title; ?></p>
    </div>
<?php endif; ?>





