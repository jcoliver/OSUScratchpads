<?php

/**
 * Implements hook_views_default_views().
 */
function morphbank_views_default_views(){
  $views = array();
  $view = new view();
  $view->name = 'morphbank_images';
  $view->description = '';
  $view->tag = 'default';
//  $view->base_table = 'eolapi';
  $view->base_table = 'taxonomy_term_data';// TODO: this will have to change
  $view->human_name = 'Morphbank Images';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Morphbank Images';
  $handler->display->display_options['css_class'] = 'omega grid-4';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
//  $handler->display->display_options['style_plugin'] = 'eolapi';
//  $handler->display->display_options['style_plugin'] = 'slideshow';// TODO: is this right?
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['wrapper_class'] = 'media-gallery';
  // see linkes 2015-2018 in scratchpads_species.views_default.inc


  //TODO: there are many additional style_options in scratchpads_species.views_default.inc ~line 419
  $handler->display->display_options['row_plugin'] = 'entity';// TODO: this needs to change
  $handler->display->display_options['row_options']['view_mode'] = 'teaser';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Field: Taxonomy term data: tid  //TODO: this should probably be replaced by morphbank table fields */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  /* Sorts criterion: Taxonomy term data: name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  // copied from lines 2023-2037 from scratchpads_species.views_default.inc
  /* Contextual filter: Field: Taxonomic name (field_taxonomic_name) */
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['id'] = 'field_taxonomic_name_tid';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['table'] = 'field_data_field_taxonomic_name';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['field'] = 'field_taxonomic_name_tid';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['default_argument_options']['term_page'] = 1;
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['default_argument_options']['node'] = 0;
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['default_argument_options']['limit'] = 0;
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['break_phrase'] = 1;
  $handler->display->display_options['arguments']['field_taxonomic_name_tid']['not'] = 0;

  /* Contextual filter: Encyclopaedia of Life data: Taxonomy field (eolapi_taxonomy)
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['id'] = 'eolapi_taxonomy_tid';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['table'] = 'field_data_eolapi_taxonomy';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['field'] = 'eolapi_taxonomy_tid';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_argument_options']['term_page'] = 1;
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_argument_options']['node'] = 0;
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_argument_options']['limit'] = 0;
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['eolapi_taxonomy_tid']['not'] = 0;
  /* Filter criterion: Encyclopaedia of Life data: Type
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eolapi';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
      'stillimage' => 'stillimage'
  );
  /* Filter criterion: Encyclopaedia of Life data: Taxonomy field (eolapi_taxonomy)
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['id'] = 'eolapi_taxonomy_tid';
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['table'] = 'field_data_eolapi_taxonomy';
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['field'] = 'eolapi_taxonomy_tid';
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['type'] = 'select';
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['vocabulary'] = 'species_dictionary';
  $handler->display->display_options['filters']['eolapi_taxonomy_tid']['hierarchy'] = 1;
  /* Filter criterion: Encyclopaedia of Life data: Source
  $handler->display->display_options['filters']['source']['id'] = 'source';
  $handler->display->display_options['filters']['source']['table'] = 'eolapi';
  $handler->display->display_options['filters']['source']['field'] = 'source';
  $handler->display->display_options['filters']['source']['value'] = 'SOF';
  */
  // Copied from lines 2056-2058 scratchpads_species.views_default.inc
  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'view-inline-filters grid-8 alpha omega';
  $views[$view->name] = $view;
  return $views;
}
