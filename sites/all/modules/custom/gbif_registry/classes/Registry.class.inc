<?php
/**
 * Standard PHP class for interacting with the GBIF registry.
 *
 * Copyright (C) 2012 Simon David Rycroft
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author s.rycroft@nhm.ac.uk
 */
namespace GBIF;

/**
 * The Registry class is the central access point to all other GBIF Registy
 * functions.
 * This class provides the functions for accessing the registry, and
 * also provides the authentication methods.
 *
 * This class should be created like:
 *
 * $gbif_registry = new GBIF\Registry();
 *
 * @author simor
 */
class Registry{
  // Note, the registryURL MUST HAVE A TRAILING SLASH.
  private $registryURL = 'http://gbrds.gbif.org/registry/';

  private $organisationKey;

  private $organisationPassword;

  private $user;

  private $password;

  private $count = 0;

  protected static $instance;

  protected function __construct(){}

  protected $registryCache = FALSE;

  /**
   * Basic singleton code copied straight from php.net
   */
  public static function singleton(){
    if(!function_exists('curl_init')){throw new Exception('CURL functions not found');}
    if(!isset(self::$instance)){
      $className = __CLASS__;
      self::$instance = new $className();
    }
    return self::$instance;
  }

  public function increment(){
    return $this->count++;
  }

  public function __clone(){
    trigger_error('Clone is not allowed.', E_USER_ERROR);
  }

  public function __wakeup(){
    trigger_error('Unserializing is not allowed.', E_USER_ERROR);
  }

  /**
   * Return an instance of the RegistryCache class.
   * This allows us to override
   * this function, and return a different class which actually does caching
   */
  public function getRegistryCache(){
    if(!$this->registryCache){
      $this->registryCache = new RegistryCache();
    }
    return $this->registryCache;
  }

  /**
   * Return the current set Registry URL.
   *
   * @return the $registryURL
   */
  public function getRegistryURL(){
    return $this->registryURL;
  }

  /**
   *
   * @param field_type $registryURL        
   */
  public function setRegistryURL($registryURL){
    // Ensure that the URL we're setting has a trailing slash, else we throw an
    // error.
    if(substr($registryURL, -1) != '/'){throw new Exception('Registry URL must have a trailing slash');}
    $this->registryURL = $registryURL;
  }

  /**
   * Simple function that returns a GBIF\Nodes object that can then be itterated
   * over to potentially return a list of all nodes.
   */
  public function getNodes($tag = FALSE, $name = FALSE){
    return new Nodes($tag, $name);
  }

  /**
   * Similar to the getNodes function, but this returns organizations.
   */
  public function getOrganizations(){
    return new Organizations(FALSE, FALSE, FALSE, FALSE);
  }

  /**
   * Same again, but returning all datasets.
   */
  public function getDatasets($type = FALSE){
    return new Datasets();
  }

  /**
   * Same again, but returning technicalInstallations
   */
  public function getTechnicalInstallations($tag = FALSE, $name = FALSE, $isoCountryCode = FALSE){
    return new TechnicalInstallations(FALSE, $tag, $name, $isoCountryCode);
  }

  /**
   * Same again, but networks
   */
  public function getNetworks(){
    return new Networks();
  }

  public function getUser(){
    return $this->user;
  }

  public function getPassword(){
    return $this->password;
  }

  public function setUser($user){
    $this->user = $user;
  }

  public function setPassword($password){
    $this->password = $password;
  }

  /**
   * http put
   *
   * FIXME - Need to add authentication to this.
   * FIXME - Should this be data, or a filename?
   */
  public function put($path, $filename){
    $ch = curl_init($this->registryURL . $path);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_PUT, TRUE);
    $file_handle = fopen($filename, 'r');
    curl_setopt($ch, CURLOPT_INFILE, $file_handle);
    curl_setopt($ch, CURLOPT_INFILESIZE, filesize($filename));
    $response = curl_exec($ch);
    print_r(curl_getinfo($ch));
    print_r(curl_errno($ch));
    print_r($response);
  }

  /**
   * http get
   *
   * We use file_get_contents here purely for its simplicity.
   */
  public function get($path, Array $parameters = array()){
    if($html = @file_get_contents($this->registryURL . $path . '?' . http_build_query($parameters))){
      return $html;
    }else{
      // FIXME: Perhaps should throw an error here rather than silently
      // failing.
      return '[]';
    }
  }

  /**
   * http post.
   */
  function post($path, $data){
    $ch = curl_init($this->registryURL . $path);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
    curl_setopt($ch, CURLOPT_USERPWD, "{$this->user}:{$this->password}");
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
      "Content-Type: application/json",
      "Accept: application/json"
    ));
    curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
    $response = curl_exec($ch);
    if(!curl_errno($ch)){
      return $response;
    }else{
      return FALSE;
    }
  }

  /**
   * http delete.
   *
   * FIXME - Need to add authentication to this.
   */
  function delete($path){
    $ch = curl_init($this->registryURL . $path);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");
    $response = curl_exec($ch);
    print_r(curl_getinfo($ch));
    print_r(curl_errno($ch));
    print_r($response);
  }

  /**
   * Simple wrapper to the get function that returns a json_decoded'd array.
   */
  public function get_json($path, Array $parameters = array()){
    // FIXME - Need to tweak the path or parameters here to ensure that we are
    // returned JSON.
    return json_decode($this->get($path, $parameters), TRUE);
  }
}