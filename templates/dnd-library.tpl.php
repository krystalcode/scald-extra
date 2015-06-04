<div class="summary">
  <div class="summary-search">
    <div class="title"><?php print $search_title; ?></div>
    <div class="small"><?php print $search_subtitle; ?></div>
  </div>

  <div class="summary-list">
    <div class="title"><?php print $list_title; ?></div>
    <div class="small"><?php print $list_subtitle; ?></div>
  </div>
</div>

<div class="scald-menu">
  <div class="add-buttons">
    <div class="toggle">
      <span class="search fa fa-search"></span>
      <span class="list fa fa-th-list"></span>
    </div>

    <div class="scald-anchor">
      <span class="fa fa-angle-double-right"></span>
      <span class="fa fa-angle-double-left"></span>
    </div>

    <?php print render($buttons); ?>
  </div>
</div>

<div class="scald-library">
  <?php print $messages; ?>
  <?php print render($list); ?>
</div>
